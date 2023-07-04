#include "BasicCalculator.hpp"
#include "IFormatter.hpp"

namespace Nummy {

    /*!
        Basic calculator with formating
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
