#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Metadata {
    std::string renderer;
    std::string tranche;
    std::string context_key;
    std::string context_value;
};

const std::vector<std::string> classic_six = {
    "code_analyzer",
    "data_processing",
    "jargon",
    "metrics",
    "network_activity",
    "system_monitoring",
};

const std::vector<std::string> modern_core = {
    "agent_workflows",
    "platform_engineering",
    "observability_ai_runtime",
    "delivery_preview_ops",
    "supply_chain_security",
};

const std::vector<std::string> ai_governance = {
    "ai_inference_ops",
    "evaluation_and_guardrails",
    "knowledge_retrieval",
    "edge_client_runtime",
    "identity_and_trust",
    "aibom_provenance",
    "agent_boundary_security",
    "embedded_agentic_pipeline",
    "data_governance_compliance",
    "finops_capacity",
};

const std::vector<std::string> security_blockchain = {
    "blockchain_protocol_ops",
    "cross_chain_interop",
    "proof_and_sequencer_ops",
};

const std::vector<std::string> overlay_quantum = {
    "hybrid_runtime_ops",
    "capacity_cost_controller",
    "batch_execution_tuner",
    "compiler_maintainer",
    "interop_adapter_engineer",
    "preflight_capacity_planner",
    "simulator_performance_engineer",
};

const std::vector<std::string> health_protocol = {
    "fhir_profile_generator",
    "smart_launch_oauth",
    "bulk_fhir_population_ops",
    "hl7v2_feed_ops",
    "clinical_workflow_events",
    "dicomweb_imaging_ops",
    "openehr_semantic_record_ops",
    "device_telemetry_clinical",
    "emr_vendor_adapter",
    "ocpp_chargepoint_ops",
    "ocpi_roaming_ops",
    "mcp_a2a_ops",
    "streaming_bus_ops",
    "service_mesh_rpc_ops",
};

std::vector<std::string> concat_all() {
    std::vector<std::string> out;
    out.insert(out.end(), classic_six.begin(), classic_six.end());
    out.insert(out.end(), modern_core.begin(), modern_core.end());
    out.insert(out.end(), ai_governance.begin(), ai_governance.end());
    out.insert(out.end(), security_blockchain.begin(), security_blockchain.end());
    out.insert(out.end(), overlay_quantum.begin(), overlay_quantum.end());
    out.insert(out.end(), health_protocol.begin(), health_protocol.end());
    return out;
}

bool contains(const std::vector<std::string>& values, const std::string& needle) {
    return std::find(values.begin(), values.end(), needle) != values.end();
}

std::string registry_id(std::string value) {
    std::replace(value.begin(), value.end(), '_', '-');
    return value;
}

std::string normalize(std::string value) {
    value.erase(value.begin(), std::find_if(value.begin(), value.end(), [](unsigned char c) {
        return !std::isspace(c);
    }));
    value.erase(std::find_if(value.rbegin(), value.rend(), [](unsigned char c) {
        return !std::isspace(c);
    }).base(), value.end());
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
        return static_cast<char>(std::tolower(c));
    });
    std::replace(value.begin(), value.end(), '-', '_');
    if (contains(concat_all(), value)) {
        return value;
    }
    return "";
}

std::string fallback_group(const std::string& family) {
    if (contains(ai_governance, family)) {
        return "ai_governance";
    }
    if (contains(security_blockchain, family)) {
        return "security_blockchain";
    }
    if (contains(overlay_quantum, family)) {
        return "overlay_quantum";
    }
    return "health_protocol";
}

Metadata metadata_for(const std::string& family) {
    if (family == "code_analyzer") {
        return {"classic-six.code_analyzer", "classic-six", "analysisFocus", "template-instantiation-audit"};
    }
    if (family == "data_processing") {
        return {"classic-six.data_processing", "classic-six", "dataWindow", "allocator-aware-streaming"};
    }
    if (family == "jargon") {
        return {"classic-six.jargon", "classic-six", "languagePolicy", "cpp-systems-glossary"};
    }
    if (family == "metrics") {
        return {"classic-six.metrics", "classic-six", "signalBlend", "latency-throughput-memory"};
    }
    if (family == "network_activity") {
        return {"classic-six.network_activity", "classic-six", "transportMix", "http-grpc-socket"};
    }
    if (family == "system_monitoring") {
        return {"classic-six.system_monitoring", "classic-six", "telemetryScope", "process-thread-runtime"};
    }
    if (family == "agent_workflows") {
        return {"modern-core.agent_workflows", "modern-core", "coordinationMode", "native-plugin-handoff"};
    }
    if (family == "platform_engineering") {
        return {"modern-core.platform_engineering", "modern-core", "platformSurface", "toolchain-release-lane"};
    }
    if (family == "observability_ai_runtime") {
        return {"modern-core.observability_ai_runtime", "modern-core", "runtimeSignals", "logs-metrics-traces"};
    }
    if (family == "delivery_preview_ops") {
        return {"modern-core.delivery_preview_ops", "modern-core", "deliveryGuardrail", "preview-binary-checkpoints"};
    }
    if (family == "supply_chain_security") {
        return {"modern-core.supply_chain_security", "modern-core", "supplyChainPosture", "compiler-linker-attestation"};
    }
    const std::string group = fallback_group(family);
    return {"fallback." + group, "fallback-" + group, "fallbackFamily", group};
}

std::string json_string(const std::string& value) {
    std::ostringstream out;
    out << '"';
    for (char c : value) {
        switch (c) {
            case '\\': out << "\\\\"; break;
            case '"': out << "\\\""; break;
            case '\n': out << "\\n"; break;
            case '\r': out << "\\r"; break;
            case '\t': out << "\\t"; break;
            default: out << c; break;
        }
    }
    out << '"';
    return out.str();
}

std::string string_array_json(const std::vector<std::string>& values) {
    std::ostringstream out;
    out << '[';
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            out << ',';
        }
        out << json_string(values[i]);
    }
    out << ']';
    return out.str();
}

std::vector<std::string> registry_ids_for(const std::vector<std::string>& values) {
    std::vector<std::string> out;
    out.reserve(values.size());
    for (const auto& value : values) {
        out.push_back(registry_id(value));
    }
    return out;
}

std::string list_values_json() {
    std::ostringstream out;
    out << "{\n";
    out << "  \"outputFormats\": [\"text\", \"json\"],\n";
    out << "  \"flags\": [\"list-values\", \"focus-family\", \"output-format\", \"seed\", \"experimental-provider\"],\n";
    out << "  \"generatorFamilies\": [\n";
    const auto families = concat_all();
    for (std::size_t i = 0; i < families.size(); ++i) {
        const auto meta = metadata_for(families[i]);
        out << "    {\"id\": " << json_string(families[i])
            << ", \"registryId\": " << json_string(registry_id(families[i]))
            << ", \"rendererKey\": " << json_string(meta.renderer)
            << ", \"tranche\": " << json_string(meta.tranche) << "}";
        if (i + 1 < families.size()) {
            out << ',';
        }
        out << '\n';
    }
    std::vector<std::string> fallback = ai_governance;
    fallback.insert(fallback.end(), security_blockchain.begin(), security_blockchain.end());
    fallback.insert(fallback.end(), overlay_quantum.begin(), overlay_quantum.end());
    fallback.insert(fallback.end(), health_protocol.begin(), health_protocol.end());
    out << "  ],\n";
    out << "  \"classicSix\": " << string_array_json(registry_ids_for(classic_six)) << ",\n";
    out << "  \"modernCore\": " << string_array_json(registry_ids_for(modern_core)) << ",\n";
    out << "  \"fallbackFamilies\": " << string_array_json(registry_ids_for(fallback)) << ",\n";
    out << "  \"implementationMode\": \"family-focus-deterministic\"\n";
    out << "}\n";
    return out.str();
}

std::uint32_t deterministic_hash(const std::string& value) {
    std::uint32_t hash = 2166136261u;
    for (unsigned char c : value) {
        hash ^= c;
        hash *= 16777619u;
    }
    return hash;
}

std::string hex_hash(std::uint32_t hash) {
    std::ostringstream out;
    out << std::hex << std::nouppercase << hash;
    return out.str();
}

std::string timestamp_for(std::uint32_t hash) {
    const auto seconds = hash % 86400u;
    const auto hour = seconds / 3600u;
    const auto minute = (seconds % 3600u) / 60u;
    const auto second = seconds % 60u;
    std::ostringstream out;
    out << "2026-01-01T" << std::setw(2) << std::setfill('0') << hour
        << ':' << std::setw(2) << minute
        << ':' << std::setw(2) << second << 'Z';
    return out.str();
}

std::string payload_json(const std::string& family, const std::string& seed, const std::string& output_format) {
    const auto meta = metadata_for(family);
    const auto hash = deterministic_hash(seed + "::" + family);
    const auto sequence = 1000u + (hash % 9000u);
    std::ostringstream out;
    out << "{\n";
    out << "  \"eventType\": \"stakeholder.generator.output\",\n";
    out << "  \"sequence\": " << sequence << ",\n";
    out << "  \"family\": " << json_string(family) << ",\n";
    out << "  \"message\": " << json_string("Deterministic cpp tranche for " + family) << ",\n";
    out << "  \"timestamp\": " << json_string(timestamp_for(hash)) << ",\n";
    out << "  \"context\": {\n";
    out << "    \"rendererKey\": " << json_string(meta.renderer) << ",\n";
    out << "    " << json_string(meta.context_key) << ": " << json_string(meta.context_value) << ",\n";
    out << "    \"seedFingerprint\": " << json_string(registry_id(family) + "-" + hex_hash(hash)) << ",\n";
    out << "    \"tranche\": " << json_string(meta.tranche) << ",\n";
    out << "    \"cppProfile\": \"next-20-deterministic-foundation\"\n";
    out << "  },\n";
    out << "  \"generationProvenance\": {\n";
    out << "    \"sourceRepo\": \"cpp-stakeholder\",\n";
    out << "    \"baseline\": \"next20-family-focus\",\n";
    out << "    \"experimental\": false,\n";
    out << "    \"adapterType\": \"static-catalog\",\n";
    out << "    \"promptVersion\": null\n";
    out << "  },\n";
    out << "  \"outputFormat\": " << json_string(output_format) << "\n";
    out << "}\n";
    return out.str();
}

void print_text_payload(const std::string& family, const std::string& seed) {
    const auto meta = metadata_for(family);
    const auto hash = deterministic_hash(seed + "::" + family);
    std::cout << "family: " << family << '\n';
    std::cout << "renderer: " << meta.renderer << '\n';
    std::cout << "tranche: " << meta.tranche << '\n';
    std::cout << "sequence: " << (1000u + (hash % 9000u)) << '\n';
    std::cout << "timestamp: " << timestamp_for(hash) << '\n';
    std::cout << "message: Deterministic cpp tranche for " << family << '\n';
}

int fail(const std::string& message) {
    std::cerr << message << '\n';
    return 2;
}

int main(int argc, char** argv) {
    std::string focus_family;
    std::string seed = "default-seed";
    std::string output_format = "text";
    bool list_values = false;

    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "--list-values") {
            list_values = true;
        } else if (arg == "--focus-family") {
            if (++i >= argc) {
                return fail("missing value for --focus-family");
            }
            focus_family = normalize(argv[i]);
            if (focus_family.empty()) {
                return fail(std::string("invalid --focus-family: ") + argv[i]);
            }
        } else if (arg == "--seed") {
            if (++i >= argc) {
                return fail("missing value for --seed");
            }
            seed = argv[i];
        } else if (arg == "--output-format") {
            if (++i >= argc) {
                return fail("missing value for --output-format");
            }
            output_format = argv[i];
            if (output_format != "text" && output_format != "json") {
                return fail("invalid --output-format: " + output_format);
            }
        } else if (arg == "--experimental-provider") {
            if (++i >= argc) {
                return fail("missing value for --experimental-provider");
            }
            return fail("experimental provider '" + std::string(argv[i]) + "' is not enabled in the deterministic first tranche");
        } else if (arg.rfind("--experimental-", 0) == 0) {
            return fail("experimental flags require --experimental-provider");
        } else {
            return fail("unknown argument: " + arg);
        }
    }

    if (list_values) {
        std::cout << list_values_json();
        return 0;
    }

    if (focus_family.empty()) {
        return fail("focus-family is required and must be a known generator family");
    }

    if (output_format == "json") {
        std::cout << payload_json(focus_family, seed, output_format);
    } else {
        print_text_payload(focus_family, seed);
    }
    return 0;
}
