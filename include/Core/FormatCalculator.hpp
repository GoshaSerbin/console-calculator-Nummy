#include "BasicCalculator.hpp"
#include "IFormatter.hpp"

namespace Nummy {

    /*!
        \brief Basic calculator with formating.

        Adds input and output prompt (prefix). Depends on IFormatter. By default uses Formatter, but it can be changed via setFormatter
       method.
    */
    class FormatCalculator : public BasicCalculator {
     public:
        FormatCalculator(std::istream& in,
                         std::ostream& out,
                         std::unique_ptr<IExpressionValidator> validator,
                         std::unique_ptr<IExpressionTokenizer> tokenizer,
                         std::unique_ptr<ICalculatableTree> tree,
                         std::unique_ptr<ITokensManager> tokensManager,
                         std::unique_ptr<IVariablesManager> variablesManager);

        auto setFormatter(std::unique_ptr<IFormatter> formatter) -> void;

        auto run() -> void override;

     private:
        auto inputPrompt(size_t command) -> std::string;   /// prefix before typing command
        auto outputPrompt(size_t command) -> std::string;  /// prefix before typing command

        std::unique_ptr<IFormatter> m_formatter;
    };

}  // namespace Nummy
