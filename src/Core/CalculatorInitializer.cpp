// TO DO: make other class argument parser
// check correction of arguments

#include "CalculatorInitializer.hpp"
#include "BasicCalculator.hpp"
#include "CalculatableTree.hpp"
#include "ExpressionTokenizer.hpp"
#include "ExpressionValidator.hpp"
#include "ProjectParameters.hpp"
#include "TokensManager.hpp"
#include "VariablesManager.hpp"

#include <fstream>
#include <sstream>

namespace Nummy {

    namespace {

        const std::string helpMessage =
            "-e = expression to calculate.\n-o = output. If not provided then std::cin. Otherwise name of output file.\nConsole Calculator "
            "\"Nummy\".";

        const std::string helpKey = "--help";
        const std::string inKey = "-i";
        const std::string outKey = "-o";
        const std::string expressionKey = "-e";

    }  // namespace

    auto CalculatorInitializer::makeCalculator(int argc, char** argv, std::ostream& out) -> std::unique_ptr<ICalculator> {
        std::ostream* calculatorOut = &std::cout;
        std::istream* calculatorIn = &std::cin;

        std::unique_ptr<ICalculator> calculator{};

        std::unique_ptr<IExpressionValidator> validator = std::make_unique<ExpressionValidator>();
        std::unique_ptr<IExpressionTokenizer> tokenizer = std::make_unique<ExpressionTokenizer>();

        std::unique_ptr<ITokensManager> tokensManager = std::make_unique<TokensManager>();
        std::unique_ptr<IVariablesManager> variablesManager = std::make_unique<VariablesManager>(*tokensManager);
        std::unique_ptr<ICalculatableTree> tree = std::make_unique<CalculatableTree>(*variablesManager);

        if (argc > 1 && argv[1] == helpKey) {
            out << helpMessage << std::endl;
            out << "current version " << PROJECT_VERSION << std::endl;
            return {};
        }

        std::unordered_map<std::string, std::string> args;
        for (int i = 1; i + 1 < argc; i += 2) {
            args[argv[i]] = argv[i + 1];
        }

        if (args.contains(outKey)) {
            static std::ofstream file(args[outKey]);
            if (!file.is_open()) {
                out << "Can not open file " << args[outKey] << std::endl;
                return {};
            }
            calculatorOut = &file;
        }

        if (args.contains(inKey)) {
            static std::ifstream file(args[inKey]);
            if (!file.is_open()) {
                out << "Can not open file " << args[inKey] << std::endl;
                return {};
            }
            calculatorIn = &file;
        }

        if (args.contains(expressionKey)) {
            static std::stringstream in;
            in << args[expressionKey];
            calculatorIn = &in;
        }

        return std::make_unique<BasicCalculator>(*calculatorIn, *calculatorOut, std::move(validator), std::move(tokenizer), std::move(tree),
                                                 std::move(tokensManager), std::move(variablesManager));
    }

}  // namespace Nummy
