Parser é um repositório dedicado ao estudo, implementação e experimentação de técnicas de parsing aplicadas ao processamento de linguagens formais e naturais. O projeto explora desde abordagens clássicas — como parsers LL, LR e recursivos descendentes — até métodos avançados usados em NLP, compiladores e análise semântica.

================================================================================
TECNICAS AVANÇADAS DE PARSING COM UDPipe + ONNX
C++ (STL), Make e GNU g++
================================================================================

Objetivo prático:
- Entrada: texto livre para estudo linguístico.
- Processamento: UDPipe + parser de sintagmas + reclassificação ONNX.
- Saída: árvores de sintagmas analisadas + texto anotado + métricas.

Modelo UDPipe sugerido:
- `portuguese-bosque-ud-2.5-191206.udpipe`
- Pode ser substituído por outro modelo `.udpipe` treinado por você.

------------------------------------------------------------------------------
1) LISTA DE TECNICAS AVANÇADAS (UDPipe + ONNX)
------------------------------------------------------------------------------

1. Parsing em 2 estágios (simbólico + neural)
- Estágio A (UDPipe): tokenização, sentenças, lemma, UPOS/XPOS, dependências.
- Estágio B (ONNX): classifica contexto sintagmático (NP/VP/PP/ADJP/ADVP/CP).
- Uso: melhorar cobertura em estruturas ambíguas.

2. Re-ranking de subárvores candidatas
- Gere múltiplas subárvores por heurísticas sintáticas.
- Use ONNX para pontuar cada hipótese.
- Escolha top-1 ou top-k com restrições linguísticas.

3. Parsing orientado por dependências para gerar sintagmas
- Converte árvore de dependência UDPipe em chunks sintagmáticos.
- Regras por `deprel`: `det`, `amod`, `nmod`, `obl`, `advmod`, `acl`.
- Uso: extrair NP e VP robustamente.

4. Janela de contexto multi-escala
- Contexto linear: token i-3..i+3.
- Contexto estrutural: ancestral até profundidade N.
- Contexto global: sentença inteira com pooling.

5. Features híbridas simbólicas + densas
- Simbólicas: POS, FEATS, deprel, distância ao head.
- Densas: embedding de token/subword.
- Fusão: concatenação e normalização em tensor ONNX.

6. Resolução de conflitos de fronteira sintagmática
- Penaliza sobreposição inválida entre NP/VP.
- Regras de fechamento por pontuação e conjunção.
- Útil para sentenças longas com coordenação.

7. Decodificação com constraints gramaticais
- Impõe consistência de concordância (gênero/número).
- Bloqueia spans improváveis por regras de idioma.
- Pode usar algoritmo tipo CKY com score neural.

8. Parsing incremental (edição interativa)
- Reprocessa somente sentença alterada.
- Cache por hash do texto + versão do modelo.
- Ideal para interface desktop wxWidgets.

9. Ensemble de parsers
- Parser A: regras linguísticas fortes.
- Parser B: ONNX classificador de span.
- Voto ponderado por confiança.

10. Explainability de sintagmas
- Expõe features que decidiram cada nó.
- Mostra caminho de dependência usado na decisão.
- Ajuda debug e validação linguística.

11. Quantização e otimização de inferência
- ONNX FP16/INT8 para reduzir latência.
- Batch por sentença e pré-alocação de tensores.
- Threads separadas para UI e inferência.

12. Avaliação por domínios
- Corpus técnico, jurídico, conversacional.
- Mede robustez de sintagmas em cada domínio.

------------------------------------------------------------------------------
2) METODOS DE PARSER APLICAVEIS NO PIPELINE
------------------------------------------------------------------------------

- Parser por regras (chunker): rápido, controlável.
- Parser de dependências (UDPipe): base estrutural principal.
- Chart parser (CKY/Earley): útil para ambiguidades e hipóteses múltiplas.
- Transição (shift-reduce): eficiente para tempo real.
- Parser neural de spans (ONNX): classifica fronteiras e rótulos.
- Parser híbrido (recomendado): regras + dependências + neural.

------------------------------------------------------------------------------
3) ESTRUTURA DE PROJETO (C++ STL + Make + g++)
------------------------------------------------------------------------------

Sugestão de pastas:
- `src/main.cpp`
- `src/udpipe_runner.cpp`
- `src/syntagm_parser.cpp`
- `src/onnx_context_classifier.cpp`
- `src/conllu_reader.cpp`
- `include/*.hpp`
- `models/portuguese-bosque-ud-2.5-191206.udpipe`
- `models/context_classifier.onnx`
- `data/input.txt`
- `output/trees.txt`
- `Makefile`

Makefile mínimo:

```make
CXX      := g++
CXXFLAGS := -std=c++17 -O2 -Wall -Wextra -pedantic
LDFLAGS  :=
INCLUDES := -Iinclude
SRC      := $(wildcard src/*.cpp)
OBJ      := $(SRC:.cpp=.o)
BIN      := parser_app

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(BIN)
```

------------------------------------------------------------------------------
4) EXEMPLOS DE ENTRADA E SAIDA (texto -> árvore -> texto analisado)
------------------------------------------------------------------------------

Exemplo 1
Entrada:
`O pesquisador analisou os dados com cuidado.`

Saída de sintagmas (resumo):
- [NP O pesquisador]
- [VP analisou [NP os dados] [PP com [NP cuidado]]]

Texto analisado:
`[NP O pesquisador] [VP analisou [NP os dados] [PP com [NP cuidado]]] .`

Exemplo 2
Entrada:
`A equipe que venceu o torneio recebeu o prêmio ontem.`

Saída:
- [NP A equipe [CP que [VP venceu [NP o torneio]]]]
- [VP recebeu [NP o prêmio] [ADVP ontem]]

Exemplo 3
Entrada:
`Se chover amanhã, a reunião será remarcada.`

Saída:
- [CP Se [VP chover [ADVP amanhã]]]
- [NP a reunião]
- [VP será remarcada]

------------------------------------------------------------------------------
5) EXEMPLO C++ (STL) DE PIPELINE DE ANALISE
------------------------------------------------------------------------------

```cpp
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Token {
    std::string form;
    std::string upos;
    int head = -1;
    std::string deprel;
};

struct Syntagm {
    std::string label;      // NP, VP, PP...
    int begin = 0;
    int end = 0;
    float score = 0.0f;     // score do ONNX
};

std::string read_text_file(const std::string& path) {
    std::ifstream in(path);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

std::vector<Token> run_udpipe(const std::string& text,
                              const std::string& udpipe_model_path) {
    (void)text;
    (void)udpipe_model_path;
    // TODO: integrar API oficial UDPipe e retornar tokens CoNLL-U.
    return {};
}

std::vector<Syntagm> build_candidates_from_dependencies(const std::vector<Token>& toks) {
    std::vector<Syntagm> out;
    // Exemplo: regra simples para NP (det + noun)
    for (size_t i = 1; i < toks.size(); ++i) {
        if (toks[i - 1].upos == "DET" && toks[i].upos == "NOUN") {
            out.push_back({"NP", static_cast<int>(i - 1), static_cast<int>(i), 0.0f});
        }
    }
    return out;
}

void classify_with_onnx(std::vector<Syntagm>& cands,
                        const std::vector<Token>& toks,
                        const std::string& onnx_path) {
    (void)toks;
    (void)onnx_path;
    // TODO: extrair features e rodar ONNX Runtime.
    for (auto& c : cands) c.score = 0.90f; // mock
}

void print_annotated_text(const std::vector<Token>& toks, const std::vector<Syntagm>& syns) {
    std::vector<std::string> open_tag(toks.size()), close_tag(toks.size());
    for (const auto& s : syns) {
        if (s.begin >= 0 && s.begin < (int)toks.size()) open_tag[s.begin] += "[" + s.label + " ";
        if (s.end >= 0 && s.end < (int)toks.size()) close_tag[s.end] = "]" + close_tag[s.end];
    }
    for (size_t i = 0; i < toks.size(); ++i) {
        std::cout << open_tag[i] << toks[i].form << close_tag[i] << " ";
    }
    std::cout << "\n";
}

int main() {
    const std::string input = read_text_file("data/input.txt");
    auto tokens = run_udpipe(input, "models/portuguese-bosque-ud-2.5-191206.udpipe");
    auto cands = build_candidates_from_dependencies(tokens);
    classify_with_onnx(cands, tokens, "models/context_classifier.onnx");
    print_annotated_text(tokens, cands);
    return 0;
}
```

------------------------------------------------------------------------------
6) EXEMPLO DE ADAPTACAO DE MODELO .ONNX (TREINO + EXPORT)
------------------------------------------------------------------------------

Observação importante:
- O arquivo `.onnx` é normalmente para inferência.
- O treino geralmente ocorre em PyTorch/TensorFlow e depois exporta para ONNX.

Fluxo recomendado:
1. Treine classificador de spans/contexto (NP/VP/PP/...) em Python.
2. Exporte modelo para `context_classifier.onnx`.
3. Carregue no C++ via ONNX Runtime.

Exemplo de export (PyTorch -> ONNX):

```python
import torch

class SpanClassifier(torch.nn.Module):
    def __init__(self, in_dim=256, hidden=128, n_classes=6):
        super().__init__()
        self.net = torch.nn.Sequential(
            torch.nn.Linear(in_dim, hidden),
            torch.nn.ReLU(),
            torch.nn.Linear(hidden, n_classes)
        )

    def forward(self, x):
        return self.net(x)

model = SpanClassifier()
model.eval()
dummy = torch.randn(1, 256)

torch.onnx.export(
    model,
    dummy,
    "context_classifier.onnx",
    input_names=["features"],
    output_names=["logits"],
    dynamic_axes={"features": {0: "batch"}, "logits": {0: "batch"}},
    opset_version=17
)
```

------------------------------------------------------------------------------
7) MODELO UDPipe BOSQUE: COMO USAR NO PROJETO
------------------------------------------------------------------------------

- Coloque o modelo em: `models/portuguese-bosque-ud-2.5-191206.udpipe`
- Se quiser trocar: mantenha a mesma interface de saída CoNLL-U.
- Para treino de novo modelo UDPipe:
  - preparar corpus UD em CoNLL-U (treino/dev/teste)
  - treinar tokenizer/tagger/parser no ecossistema UDPipe
  - salvar novo `.udpipe` e versionar metadados do treino

------------------------------------------------------------------------------
8) APLICACOES REAIS
------------------------------------------------------------------------------

- Corretor gramatical com sugestões por sintagma.
- Extração de informação (sujeito, predicado, complementos).
- Simplificação textual baseada em árvores.
- Classificação semântica de sentenças técnicas.
- Assistente educacional para análise sintática.

Resultado esperado:
- Pipeline robusto para português com entrada textual livre,
- saída de árvores de sintagmas,
- e texto final anotado para estudo linguístico e integração em UI.
