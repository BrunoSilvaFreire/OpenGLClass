
#include <flutter/method_channel.h>
#include <flutter/plugin_registrar.h>
#include <flutter/standard_method_codec.h>
#include <sys/utsname.h>
#include <memory>
#include <sstream>

static const std::string kUnnecessaryGetModulesMethod = "get_unnecessary_modules";
static const std::string kUnnecessaryGetModulesStatusMethod = "get_unnecessary_module_status";


namespace {

    class UnnecessaryPlugin : public flutter::Plugin {
    public:
        static void RegisterWithRegistrar(flutter::PluginRegistrar *registrar);

        // Creates a plugin that communicates on the given channel.
        UnnecessaryPlugin(
                std::unique_ptr <flutter::MethodChannel<flutter::EncodableValue>> channel
        );

        virtual ~UnnecessaryPlugin();

    private:
        // Called when a method is called on |channel_|;
        void HandleMethodCall(
                const flutter::MethodCall <flutter::EncodableValue> &method_call,
                std::unique_ptr <flutter::MethodResult<flutter::EncodableValue>> result
        );

        // The MethodChannel used for communication with the Flutter engine.
        std::unique_ptr <flutter::MethodChannel<flutter::EncodableValue>> channel_;
    };

// static
    void UnnecessaryPlugin::RegisterWithRegistrar(flutter::PluginRegistrar *registrar) {
        auto channel = std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
            registrar->messenger(),
            "get_unnecessary_modules",
            &flutter::StandardMethodCodec::GetInstance()
        );
        auto *channel_pointer = channel.get();

        auto plugin = std::make_unique<UnnecessaryPlugin>(std::move(channel));

        channel_pointer->SetMethodCallHandler(
                [plugin_pointer = plugin.get()](const auto &call, auto result) {
                    plugin_pointer->HandleMethodCall(call, std::move(result));
                }
        );

        registrar->AddPlugin(std::move(plugin));
    }

    UnnecessaryPlugin::UnnecessaryPlugin(
            std::unique_ptr <flutter::MethodChannel<flutter::EncodableValue>> channel
    )
            : channel_(std::move(channel)) {}

    UnnecessaryPlugin::~UnnecessaryPlugin() {};

    void UnnecessaryPlugin::HandleMethodCall(
            const flutter::MethodCall <flutter::EncodableValue> &method_call,
            std::unique_ptr <flutter::MethodResult<flutter::EncodableValue>> result
    ) {
        if (method_call.method_name().compare("getPlatformVersion") == 0) {
            struct utsname uname_data = {};
            uname(&uname_data);
            std::ostringstream version_stream;
            version_stream << "Linux " << uname_data.version;
            flutter::EncodableValue response(version_stream.str());
            result->Success(&response);
        } else {
            result->NotImplemented();
        }
    }

}  // namespace

void UnnecessaryPluginRegisterWithRegistrar(DesktopPluginRegistrarRef registrar) {
    static auto *plugin_registrar = new flutter::PluginRegistrar(registrar);

    UnnecessaryPlugin::RegisterWithRegistrar(plugin_registrar);
}