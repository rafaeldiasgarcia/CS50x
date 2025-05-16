from flask import Flask, render_template
import random
import os

app = Flask(__name__)

PALAVRAS_ARQUIVO = os.path.join(app.static_folder, 'data', 'words.txt')

def carregar_palavras(caminho_arquivo):
    """Carrega palavras de um arquivo, uma por linha, e as retorna em maiúsculas."""
    try:
        with open(caminho_arquivo, 'r', encoding='utf-8') as f:
            palavras = [linha.strip().upper() for linha in f if linha.strip()]
        palavras_filtradas = [p for p in palavras if len(p) == 5 and p.isalpha()]
        if not palavras_filtradas:
            print(f"Aviso: Nenhuma palavra válida de 5 letras encontrada em {caminho_arquivo}. Usando lista de fallback.")
            return ["TERMO", "SAGAZ", "NOBRE", "AMIGO", "IDEIA"]
        return palavras_filtradas
    except FileNotFoundError:
        print(f"Erro: Arquivo de palavras não encontrado em {caminho_arquivo}. Usando lista de fallback.")
        return ["TERMO", "SAGAZ", "NOBRE", "AMIGO", "IDEIA"]

lista_de_palavras_validas = carregar_palavras(PALAVRAS_ARQUIVO)

@app.route("/")
def index():
    palavra_secreta_escolhida = random.choice(lista_de_palavras_validas) if lista_de_palavras_validas else "ERRO"
    return render_template("index.html", palavra_secreta=palavra_secreta_escolhida, palavras_validas=lista_de_palavras_validas)

if __name__ == "__main__":
    app.run(debug=True)
