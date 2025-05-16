document.addEventListener('DOMContentLoaded', () => {
    const TAMANHO_PALAVRA = 5;
    const MAX_TENTATIVAS = 6;

    const gradeContainer = document.getElementById('grade-container');
    const tecladoContainer = document.getElementById('teclado-container');
    const mensagensContainer = document.getElementById('mensagens-container');

    const controlesFimJogoDiv = document.getElementById('controles-fim-jogo');
    const btnJogarNovamente = document.getElementById('btn-jogar-novamente');

    let linhaAtual = 0;
    let colunaAtual = 0;
    let palavraSecreta = PALAVRA_SECRETA_SERVIDOR;
    const listaPalavrasValidas = new Set(LISTA_PALAVRAS_VALIDAS_SERVIDOR);

    let grade = [];
    let historicoTeclas = {};
    let jogoAtivo = true;

    const layoutTeclado = [
        ["Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P"],
        ["A", "S", "D", "F", "G", "H", "J", "K", "L", "Ç"],
        ["ENTER", "Z", "X", "C", "V", "B", "N", "M", "BACKSPACE"]
    ];

    function inicializarGrade() {
        gradeContainer.innerHTML = '';
        grade = [];
        for (let i = 0; i < MAX_TENTATIVAS; i++) {
            let linha = document.createElement('div');
            linha.classList.add('linha-grade');
            let celulasLinha = [];
            for (let j = 0; j < TAMANHO_PALAVRA; j++) {
                let celula = document.createElement('div');
                celula.classList.add('celula-grade');
                linha.appendChild(celula);
                celulasLinha.push(celula);
            }
            gradeContainer.appendChild(linha);
            grade.push(celulasLinha);
        }
    }

    function inicializarTeclado() {
        tecladoContainer.innerHTML = '';
        layoutTeclado.forEach(linhaTeclas => {
            const linhaDiv = document.createElement('div');
            linhaDiv.classList.add('linha-teclado');
            linhaTeclas.forEach(tecla => {
                const teclaButton = document.createElement('button');
                teclaButton.classList.add('tecla');
                teclaButton.textContent = tecla;
                teclaButton.dataset.key = tecla.toUpperCase();
                if (tecla === "ENTER" || tecla === "BACKSPACE") {
                    teclaButton.style.minWidth = "60px";
                }
                teclaButton.addEventListener('click', () => lidarComCliqueTecla(tecla.toUpperCase()));
                linhaDiv.appendChild(teclaButton);
            });
            tecladoContainer.appendChild(linhaDiv);
        });
    }

    function lidarComCliqueTecla(tecla) {
        console.log("Tecla clicada:", tecla);
        if (!jogoAtivo) return;

        if (tecla === "BACKSPACE") {
            apagarLetra();
        } else if (tecla === "ENTER") {
            submeterTentativa();
        } else if (tecla.length === 1 && tecla >= "A" && tecla <= "Z" || tecla === "Ç") {
            adicionarLetra(tecla);
        }
    }

    function lidarComTeclaFisica(evento) {
        const { key } = evento;
        console.log("Tecla física:", key);
        if (!jogoAtivo) return;

        if (key === "Backspace") {
            apagarLetra();
        } else if (key === "Enter") {
            submeterTentativa();
        } else if (key.length === 1 && ((key.toUpperCase() >= "A" && key.toUpperCase() <= "Z") || key.toUpperCase() === "Ç")) {
            adicionarLetra(key.toUpperCase());
        }
    }

    function adicionarLetra(letra) {
        if (colunaAtual < TAMANHO_PALAVRA && linhaAtual < MAX_TENTATIVAS && jogoAtivo) {
            const celula = grade[linhaAtual][colunaAtual];
            celula.textContent = letra;
            colunaAtual++;
        }
    }

    function apagarLetra() {
        if (colunaAtual > 0) {
            colunaAtual--;
            const celula = grade[linhaAtual][colunaAtual];
            celula.textContent = '';
        }
    }

    function submeterTentativa() {
        if (!jogoAtivo) return;

        if (colunaAtual !== TAMANHO_PALAVRA) {
            mostrarMensagem("Palavra incompleta!");
            agitarLinhaAtual();
            return;
        }

        let tentativaAtual = "";
        for (let i = 0; i < TAMANHO_PALAVRA; i++) {
            tentativaAtual += grade[linhaAtual][i].textContent;
        }

        console.log("Tentativa submetida:", tentativaAtual);
        processarTentativa(tentativaAtual);

        if (tentativaAtual.toUpperCase() === palavraSecreta.toUpperCase()) {
            jogoAtivo = false;
            mostrarMensagem("Parabéns, você acertou!", true);
            mostrarBotaoJogarNovamente();
            animarVitoria();
            return;
        }

        linhaAtual++;
        colunaAtual = 0;

        if (linhaAtual === MAX_TENTATIVAS) {
            jogoAtivo = false;
            mostrarMensagem(`Fim de jogo! A palavra era: ${palavraSecreta.toUpperCase()}`, false);
            mostrarBotaoJogarNovamente();
        }
    }

    function processarTentativa(tentativa) {
        let palavraSecretaMaiuscula = palavraSecreta.toUpperCase();
        let tentativaMaiuscula = tentativa.toUpperCase();

        let contagemLetrasSecretas = {};
        for (let letra of palavraSecretaMaiuscula) {
            contagemLetrasSecretas[letra] = (contagemLetrasSecretas[letra] || 0) + 1;
        }

        const linhaGradeAtual = grade[linhaAtual];
        let statusTentativa = new Array(TAMANHO_PALAVRA).fill(null);

        for (let i = 0; i < TAMANHO_PALAVRA; i++) {
            const letraTentativa = tentativaMaiuscula[i];
            if (letraTentativa === palavraSecretaMaiuscula[i]) {
                statusTentativa[i] = 'correta';
                contagemLetrasSecretas[letraTentativa]--;
            }
        }

        for (let i = 0; i < TAMANHO_PALAVRA; i++) {
            if (statusTentativa[i] === 'correta') continue;

            const letraTentativa = tentativaMaiuscula[i];
            if (palavraSecretaMaiuscula.includes(letraTentativa) && contagemLetrasSecretas[letraTentativa] > 0) {
                statusTentativa[i] = 'presente';
                contagemLetrasSecretas[letraTentativa]--;
            } else {
                statusTentativa[i] = 'ausente';
            }
        }

        for (let i = 0; i < TAMANHO_PALAVRA; i++) {
            const celula = linhaGradeAtual[i];
            const statusFinalLetra = statusTentativa[i];
            const letraDaCelula = tentativaMaiuscula[i];

            celula.classList.add('flip');

            setTimeout(() => {
                if (statusFinalLetra === 'correta') {
                    celula.classList.add('correta');
                } else if (statusFinalLetra === 'presente') {
                    celula.classList.add('presente');
                } else {
                    celula.classList.add('ausente');
                }
                atualizarCorTecla(letraDaCelula, statusFinalLetra);
            }, i * 250 + 250);
        }
    }

    function atualizarCorTecla(letra, classeStatusGrade) {
        const tecla = tecladoContainer.querySelector(`button[data-key="${letra}"]`);
        if (tecla) {
            if (classeStatusGrade === 'correta') {
                tecla.classList.remove('presente', 'ausente');
                tecla.classList.add('correta');
                historicoTeclas[letra] = 'correta';
            } else if (classeStatusGrade === 'presente' && historicoTeclas[letra] !== 'correta') {
                tecla.classList.remove('ausente');
                tecla.classList.add('presente');
                historicoTeclas[letra] = 'presente';
            } else if (classeStatusGrade === 'ausente' && !historicoTeclas[letra]) {
                tecla.classList.add('ausente');
                historicoTeclas[letra] = 'ausente';
            }
        }
    }

    function mostrarMensagem(msg, sucesso = null) {
        mensagensContainer.textContent = msg;
        mensagensContainer.classList.remove('sucesso', 'erro', 'aviso');

        if (sucesso === true) {
            mensagensContainer.classList.add('sucesso');
        } else if (sucesso === false) {
            mensagensContainer.classList.add('erro');
        } else {
            mensagensContainer.classList.add('aviso');
        }

        if (jogoAtivo || (sucesso !== true && sucesso !== false) ){
            setTimeout(() => {
                if (mensagensContainer.textContent === msg) {
                     mensagensContainer.textContent = '';
                     mensagensContainer.classList.remove('sucesso', 'erro', 'aviso');
                }
            }, 2000);
        }
    }

    function desabilitarEntrada() {
        jogoAtivo = false;
        console.log("Entrada desabilitada.");
    }

    function reiniciarJogo() {
        window.location.reload();
    }

    function mostrarBotaoJogarNovamente() {
        controlesFimJogoDiv.style.display = 'block';
    }

    function agitarLinhaAtual() {
        const linhaDiv = gradeContainer.children[linhaAtual];
        if (linhaDiv) {
            linhaDiv.classList.add('shake');
            setTimeout(() => {
                linhaDiv.classList.remove('shake');
            }, 500);
        }
    }

    function animarVitoria() {
        const linhaVitoria = grade[linhaAtual-1];
        if(!linhaVitoria) return;

        linhaVitoria.forEach((celula, index) => {
            setTimeout(() => {
                celula.classList.add('dance');
            }, index * 100);
        });
    }

    inicializarGrade();
    inicializarTeclado();
    document.addEventListener('keydown', lidarComTeclaFisica);
    btnJogarNovamente.addEventListener('click', reiniciarJogo);

    console.log("Jogo Termo Clone inicializado!");
    console.log("Palavra secreta (para debug):", palavraSecreta);
    console.log("Lista de palavras válidas (primeiras 10 para debug):", LISTA_PALAVRAS_VALIDAS_SERVIDOR.slice(0,10));
});
