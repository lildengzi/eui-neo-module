#include "core/render/shadertoy.h"

#include "eui/json.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

namespace core::render {
namespace {

bool integer(const eui::json::Value& value, int& output) {
    std::int64_t signedValue = 0;
    std::uint64_t unsignedValue = 0;
    if (value.signedInteger(signedValue)) {
        output = static_cast<int>(signedValue);
        return true;
    }
    if (value.unsignedInteger(unsignedValue)) {
        output = static_cast<int>(unsignedValue);
        return true;
    }
    return false;
}


void setError(ShaderToyError& error,
              const std::string& source,
              std::string message) {
    error = {ShaderToyErrorCode::SourceReadFailed, {}, {}, "graph-json",
             source, 0, std::move(message)};
}

std::string resolvedPath(const std::filesystem::path& base,
                         const std::string& value) {
    if (value.empty()) return {};
    const std::filesystem::path path = std::filesystem::u8path(value);
    return (path.is_absolute() ? path : base / path).lexically_normal().u8string();
}

bool parseArrayGraph(const eui::json::Value& passes,
                     const std::filesystem::path& base,
                     ShaderToyGraph& graph,
                     ShaderToyError& error) {
    if (passes.size() == 0) {
        setError(error, {}, "Array graph JSON requires at least one pass.");
        return false;
    }
    graph = {};
    for (std::size_t index = 0; index < passes.size(); ++index) {
        graph.addPass(
            "pass" + std::to_string(index),
            (base / "frag" /
             (std::to_string(index + 1) + ".frag")).u8string());
    }
    for (std::size_t passIndex = 0; passIndex < passes.size(); ++passIndex) {
        const eui::json::Value channels = passes.at(passIndex);
        if (channels.type() != eui::json::Type::Array ||
            channels.size() != kShaderToyChannelCount) {
            setError(error, {}, "Each array pass must define four channels.");
            return false;
        }
        for (std::size_t channelIndex = 0;
             channelIndex < kShaderToyChannelCount;
             ++channelIndex) {
            const eui::json::Value value = channels.at(channelIndex);
            int type = 0;
            int bufferIndex = -1;
            if (!integer(value.get("type"), type) ||
                !integer(value.get("bufferIndex"), bufferIndex)) {
                setError(error, {},
                         "Array channels require integer type and bufferIndex.");
                return false;
            }
            ShaderToyChannel channel = ShaderToyChannel::none();
            if (type == 1) {
                std::string image;
                if (!value.get("imagePath").string(image) &&
                    !value.get("imageName").string(image)) {
                    setError(error, {},
                             "Array image channel requires imagePath or imageName.");
                    return false;
                }
                channel = ShaderToyChannel::image(
                    resolvedPath(base / "iChannel", image));
            } else if (type == 2) {
                if (bufferIndex < 0 ||
                    bufferIndex >= static_cast<int>(passes.size())) {
                    setError(error, {}, "Array bufferIndex is out of range.");
                    return false;
                }
                channel = bufferIndex == static_cast<int>(passIndex)
                    ? ShaderToyChannel::self()
                    : ShaderToyChannel::buffer(
                          "pass" + std::to_string(bufferIndex));
            } else if (type != 0) {
                setError(error, {}, "Array channel type is unsupported.");
                return false;
            }
            graph.setChannel("pass" + std::to_string(passIndex),
                             channelIndex, std::move(channel));
        }
    }
    return true;
}

bool parseChannel(const eui::json::Value& value,
                  const std::filesystem::path& base,
                  ShaderToyChannel& channel,
                  ShaderToyError& error) {
    if (value.type() != eui::json::Type::Object) {
        setError(error, {}, "Channel must be an object.");
        return false;
    }
    std::string kind;
    if (!value.get("kind").string(kind)) {
        setError(error, {}, "Channel requires a kind.");
        return false;
    }
    std::string source;
    value.get("source").string(source);
    if (kind == "none") channel = ShaderToyChannel::none();
    else if (kind == "self") channel = ShaderToyChannel::self();
    else if (kind == "buffer") channel = ShaderToyChannel::buffer(source);
    else if (kind == "image") {
        channel = ShaderToyChannel::image(resolvedPath(base, source));
    } else {
        setError(error, {}, "Unknown Shadertoy channel kind: " + kind);
        return false;
    }
    return true;
}

bool parseEuiGraph(const eui::json::Value& root,
                   const eui::json::Value& passes,
                   const std::filesystem::path& base,
                   ShaderToyGraph& graph,
                   ShaderToyError& error) {
    int version = 0;
    if (!integer(root.get("version"), version) || version != 1) {
        setError(error, {}, "EUI Shadertoy graph version must be 1.");
        return false;
    }
    graph = {};
    for (std::size_t passIndex = 0; passIndex < passes.size(); ++passIndex) {
        const eui::json::Value value = passes.at(passIndex);
        if (value.type() != eui::json::Type::Object) {
            setError(error, {}, "EUI graph passes must be objects.");
            return false;
        }
        std::string name;
        std::string source;
        std::string inlineSource;
        std::string spirv;
        std::string sourceName;
        if (!value.get("name").string(name)) {
            setError(error, {}, "EUI graph pass requires a name.");
            return false;
        }
        value.get("source").string(source);
        value.get("inlineSource").string(inlineSource);
        value.get("spirv").string(spirv);
        value.get("sourceName").string(sourceName);
        if (!source.empty() && !inlineSource.empty()) {
            setError(error, {},
                     "A pass cannot define both source and inlineSource.");
            return false;
        }
        if (!inlineSource.empty()) {
            graph.addInlinePass(name, inlineSource,
                                resolvedPath(base, spirv),
                                sourceName);
        } else {
            graph.addPass(name, resolvedPath(base, source),
                          resolvedPath(base, spirv));
        }
        const eui::json::Value channels = value.get("channels");
        if (channels.valid()) {
            if (channels.type() != eui::json::Type::Array ||
                channels.size() > kShaderToyChannelCount) {
                setError(error, {},
                         "Pass channels must be an array of at most four entries.");
                return false;
            }
            for (std::size_t channelIndex = 0;
                 channelIndex < channels.size();
                 ++channelIndex) {
                ShaderToyChannel channel;
                if (!parseChannel(channels.at(channelIndex), base,
                                  channel, error)) {
                    return false;
                }
                graph.setChannel(name, channelIndex, std::move(channel));
            }
        }
    }
    const eui::json::Value uniforms = root.get("uniforms");
    if (uniforms.valid()) {
        if (uniforms.type() != eui::json::Type::Array) {
            setError(error, {}, "EUI graph uniforms must be an array.");
            return false;
        }
        for (std::size_t index = 0; index < uniforms.size(); ++index) {
            const eui::json::Value value = uniforms.at(index);
            std::string name;
            std::string type;
            if (value.type() != eui::json::Type::Object ||
                !value.get("name").string(name) ||
                !value.get("type").string(type)) {
                setError(error, {},
                         "Each EUI graph uniform requires name and type.");
                return false;
            }
            const eui::json::Value components = value.get("value");
            auto number = [&](std::size_t component, float& output) {
                double parsed = 0.0;
                if (components.type() == eui::json::Type::Array) {
                    if (!components.at(component).number(parsed)) return false;
                } else if (component == 0) {
                    if (!components.number(parsed)) return false;
                } else {
                    return false;
                }
                output = static_cast<float>(parsed);
                return true;
            };
            float values[4]{};
            if (type == "float") {
                if (!number(0, values[0])) {
                    setError(error, {}, "Float uniform value must be numeric.");
                    return false;
                }
                graph.setUniform(name, values[0]);
            } else if (type == "int") {
                int parsed = 0;
                if (!integer(components, parsed)) {
                    setError(error, {}, "Int uniform value must be an integer.");
                    return false;
                }
                graph.setUniform(name, parsed);
            } else if (type == "vec2") {
                if (!number(0, values[0]) || !number(1, values[1])) {
                    setError(error, {}, "vec2 uniform value requires two numbers.");
                    return false;
                }
                graph.setUniform(name, Vec2{values[0], values[1]});
            } else if (type == "vec3") {
                if (!number(0, values[0]) || !number(1, values[1]) ||
                    !number(2, values[2])) {
                    setError(error, {}, "vec3 uniform value requires three numbers.");
                    return false;
                }
                graph.setUniform(
                    name, Vec3{values[0], values[1], values[2]});
            } else if (type == "vec4") {
                if (!number(0, values[0]) || !number(1, values[1]) ||
                    !number(2, values[2]) || !number(3, values[3])) {
                    setError(error, {}, "vec4 uniform value requires four numbers.");
                    return false;
                }
                graph.setUniform(
                    name, Color{values[0], values[1],
                                values[2], values[3]});
            } else {
                setError(error, {}, "Unknown EUI graph uniform type: " + type);
                return false;
            }
        }
    }
    return true;
}

} // namespace

bool parseShaderToyGraphJson(const std::string& json,
                             const std::string& baseDirectory,
                             ShaderToyGraph& graph,
                             ShaderToyError& error) {
    eui::json::Document document;
    if (!document.parse(json)) {
        setError(error, {}, document.error().message);
        error.line = static_cast<int>(document.error().offset);
        return false;
    }
    const eui::json::Value root = document.root();
    const eui::json::Value passes = root.get("passes");
    if (passes.type() != eui::json::Type::Array) {
        setError(error, {}, "Shadertoy graph JSON requires a passes array.");
        return false;
    }
    const std::filesystem::path base =
        std::filesystem::u8path(baseDirectory);
    const bool parsed = passes.size() > 0 &&
                        passes.at(0).type() == eui::json::Type::Array
        ? parseArrayGraph(passes, base, graph, error)
        : parseEuiGraph(root, passes, base, graph, error);
    if (!parsed) return false;
    const ShaderToyValidationResult validation =
        validateShaderToyGraph(graph);
    if (!validation.valid()) {
        error = validation.errors.front();
        return false;
    }
    error = {};
    return true;
}

bool loadShaderToyGraphJson(const std::string& path,
                            ShaderToyGraph& graph,
                            ShaderToyError& error) {
    std::ifstream input(std::filesystem::u8path(path), std::ios::binary);
    if (!input) {
        setError(error, path, "Unable to read Shadertoy graph JSON.");
        return false;
    }
    std::ostringstream contents;
    contents << input.rdbuf();
    const std::filesystem::path parent =
        std::filesystem::u8path(path).parent_path();
    if (!parseShaderToyGraphJson(contents.str(), parent.u8string(),
                                 graph, error)) {
        if (error.sourcePath.empty()) error.sourcePath = path;
        return false;
    }
    return true;
}

} // namespace core::render
