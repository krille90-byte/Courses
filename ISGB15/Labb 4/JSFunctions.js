/* Grupp 35, Arvid Rimmerfors, Christer Linde, Martin Persson */
"use strict";

// Dumt, vad ska Olle, Ida, Eric, Adam och Max göra? Diskriminering.
const MIN_NAME_LEN = 5;

/**
 * Globalt objekt som innehåller de attribut som ni skall använda.
 * Initieras genom anrop till funktionern initGlobalObject().
 */
let oGameData = {};

let centisecondsElapsed = 0;
let maxTime = 5 * 10;
let timerVar;

/**
 * Initerar det globala objektet med de attribut som ni skall använda er av.
 * Funktionen tar inte emot några värden.
 * Funktionen returnerar inte något värde.
 */
oGameData.initGlobalObject = function() {

    // Datastruktur för vilka platser som är lediga respektive har brickor
    oGameData.gameField = Array('', '', '', '', '', '', '', '', '');
    
    /* Testdata för att testa rättningslösning */
    // 
    // oGameData.gameField = Array('X', 'X', 'X', '', '', '', '', '', '');
    // oGameData.gameField = Array('X', '', '', 'X', '', '', 'X', '', '');
    // oGameData.gameField = Array('X', '', '', '', 'X', '', '', '', 'X');
    // oGameData.gameField = Array('', '', 'X', '', 'X', '', 'X', '', '');
    // oGameData.gameField = Array('X', 'O', 'X', '0', 'X', 'O', 'O', 'X', 'O');

    // Indikerar tecknet som skall användas för spelare ett.
    oGameData.playerOne = "X";

    // Indikerar tecknet som skall användas för spelare två.
    oGameData.playerTwo = "O";

    // Kan anta värdet X eller O och indikerar vilken spelare som för tillfället skall lägga sin "bricka".
    oGameData.currentPlayer = "";

    // Nickname för spelare ett som tilldelas från ett formulärelement,
    oGameData.nickNamePlayerOne = "";

    // Nickname för spelare två som tilldelas från ett formulärelement.
    oGameData.nickNamePlayerTwo = "";

    // Färg för spelare ett som tilldelas från ett formulärelement.
    oGameData.colorPlayerOne = "";

    // Färg för spelare två som tilldelas från ett formulärelement.
    oGameData.colorPlayerTwo = "";

    // "Flagga" som indikerar om användaren klickat för checkboken.
    oGameData.timerEnabled = false;
}

/**
 * Kontrollerar för tre i rad.
 * Returnerar 0 om det inte är någon vinnare, 
 * returnerar 1 om spelaren med ett kryss (X) är vinnare,
 * returnerar 2 om spelaren med en cirkel (O) är vinnare eller
 * returnerar 3 om det är oavgjort.
 * Funktionen tar inte emot några värden.
 */
oGameData.checkForGameOver = function() {
    let result = oGameData.gameField; // the game field, *tada*
    let winCondition = [ [0,1,2], [3,4,5], [6,7,8], [0,4,8], [0,3,6], [1,4,7], [2,5,8], [6,4,2] ]; // all the ways someone can win

    for(let i = 0; i < winCondition.length; i++) { // check all the possible combinations
        if(result[winCondition[i][0]] == result[winCondition[i][1]] && result[winCondition[i][1]] == result[winCondition[i][2]]) { // there's a win
            if(result[winCondition[i][0]] == "X") // x won
                return 1;
            else if(result[winCondition[i][0]] == "O") // o won
                return 2;
        }
    }

    for(let i = 0; i < result.length; i++) {
        if(result[i] == "")
            return 0; // no winner yet
    }

    return 3; // tie
}

window.addEventListener('load', (event) => {
    oGameData.initGlobalObject();
    document.querySelector("#gameArea").className = "d-none";

    let startKnapp = document.querySelector("#newGame");
    startKnapp.addEventListener("click", validateForm);

    let timerCheckbox = document.createElement("input"); // new checkbox
    timerCheckbox.type = "checkbox";
    timerCheckbox.id = "timeryesplease";
    let divInForm = document.querySelector("#divInForm");
    let divInA = document.querySelector("#divWithA");
    divInForm.insertBefore(timerCheckbox, divInA); // add checkbox to form before divInA (start button)
    let timerLabel = document.createElement("label"); // new label
    timerLabel.id = "snyggtimerlabel";
    timerLabel.appendChild(document.createTextNode("Vill du begränsa tiden till 5 sekunder per drag?"));
    divInForm.insertBefore(timerLabel, divInA); // add label to form before divInA (start button) (but after checkbox)
});

function validateForm() {
    let nick1 = document.querySelector("#nick1").value.toLowerCase();
    let nick2 = document.querySelector("#nick2").value.toLowerCase();

    let col1 = document.querySelector("#color1").value;
    let col2 = document.querySelector("#color2").value;

    try {
        if(nick1.length < MIN_NAME_LEN || nick2.length < MIN_NAME_LEN)
            throw "Namnet är för kort";
        if(nick1 == nick2)
            throw "Namnen får ej vara lika.";
        if((col1 == "#ffffff" || col1 == "#000000") || (col2 == "#ffffff" || col2 == "#000000")) // pain
            throw "Svart och vit är ej tillåtet.";
        if(col1 == col2)
            throw "Ni kan inte ha samma färg.";
    } catch(e) {
        document.querySelector("#errorMsg").textContent = e; // let the user know
        return;
    }

    initiateGame();
}

function timer() {
    centisecondsElapsed++;
    updateCountdown();

    if(centisecondsElapsed != maxTime) { return; } // only run if 5 seconds have elapsed
    if (oGameData.currentPlayer == oGameData.playerOne)
        oGameData.currentPlayer = oGameData.playerTwo;
    else
        oGameData.currentPlayer = oGameData.playerOne;
    updateJumbotron();
    centisecondsElapsed = 0;
}

function initiateGame() {
    document.querySelector("#gameArea").className = "";
    document.querySelector("#errorMsg").textContent = "";
    document.querySelector("#divInForm").className = "d-none"; // hide form

    if(document.querySelector("#timeryesplease").checked) { // check if timer is checked
        oGameData.timerEnabled = true;
        updateCountdown();
        timerVar = setInterval(timer, 100); // start timer
    }

    oGameData.nickNamePlayerOne = document.querySelector("#nick1").value;
    oGameData.nickNamePlayerTwo = document.querySelector("#nick2").value; // ok
    oGameData.colorPlayerOne = document.querySelector("#color1").value;
    oGameData.colorPlayerTwo = document.querySelector("#color2").value; // ..ok

    let allTheTDs = document.querySelectorAll("td");
    for(let i = 0; i < allTheTDs.length; i++) {
        allTheTDs[i].textContent = "";
        if(window.matchMedia('(prefers-color-scheme: dark)').matches) { // ：）
            allTheTDs[i].style.backgroundColor = "#262626";
        } else {
            allTheTDs[i].style.backgroundColor = "#e9ecef";
        }
    }

    // slumpmässig startspelare
    if(Math.random(0, 1) < 0.5) { // < 0.5
        oGameData.currentPlayer = oGameData.playerOne;
    } else { // >= 0.5
        oGameData.currentPlayer = oGameData.playerTwo;
    }

    document.querySelector(".jumbotron > h1").textContent = "Aktuell spelare må vara " +
        ((oGameData.currentPlayer == "X") ? oGameData.nickNamePlayerOne : oGameData.nickNamePlayerTwo) +
        " (" + oGameData.currentPlayer + ")"; // update jumbotron

    let gameGrid = document.querySelectorAll(".mr-auto tr td");
    for (let i = 0; i < gameGrid.length; i++)
        gameGrid[i].addEventListener("click", executeMove);
}

function executeMove(event) {
    let id = event.srcElement.dataset.id;
    let clickedTile = document.querySelector("[data-id=\"" + id + "\"]");

    if(event.srcElement.localName != "td") { return; } // endast fortsätter på td
    if(clickedTile.textContent != "") { return; } // if not blank tile

    centisecondsElapsed = 0;

    clickedTile.textContent = oGameData.currentPlayer; // place letter
    oGameData.gameField[id] = oGameData.currentPlayer; // add to gamefield
    if (oGameData.currentPlayer == "X") {
        clickedTile.style.backgroundColor = oGameData.colorPlayerOne;
        oGameData.currentPlayer = oGameData.playerTwo;
    } else {
        clickedTile.style.backgroundColor = oGameData.colorPlayerTwo;
        oGameData.currentPlayer = oGameData.playerOne;
    }
    updateJumbotron();

    /* rip min jättefina ternary mumbo jumbo //Martin               Du är ej saknad //Arvid
    let isX = (oGameData.currentPlayer == "X");
    clickedTile.textContent = isX ? "X" : "O"; // TERNARY OPERATORS LET'S GOOO
    clickedTile.style.backgroundColor = isX ? oGameData.colorPlayerOne : oGameData.colorPlayerTwo;
    document.querySelector(".jumbotron > h1").textContent = "Aktuell spelare må vara " +
        (isX ? oGameData.nickNamePlayerTwo : oGameData.nickNamePlayerOne); // update jumbotron
    oGameData.currentPlayer = isX ? "O" : "X"; */

    let gameOverStatus = oGameData.checkForGameOver();
    if(gameOverStatus != 0) {
        let gameGrid = document.querySelectorAll(".mr-auto tr td"); // remove listener
        for (let i = 0; i < gameGrid.length; i++)
            gameGrid[i].removeEventListener("click", executeMove);

        document.querySelector("#errorMsg").innerHTML = "<a onClick=\"resetGame()\">Klicka här för att spela igen.</a>";
        
        let jumbotronthefinalone = "";
        switch(gameOverStatus) {
            case 1: // x win
                jumbotronthefinalone = "Grattis " + oGameData.nickNamePlayerOne + "! Du vann."; break;
            case 2: // o win
                jumbotronthefinalone = "Grattis " + oGameData.nickNamePlayerTwo + "! Du vann."; break;
            case 3: // tie
                jumbotronthefinalone = "WOAH, det blev oavgjort!"; break;
            default: // panic, unreachable statement
                jumbotronthefinalone = "Nu hände något dumt."; break;
        }
        document.querySelector(".jumbotron > h1").textContent = jumbotronthefinalone;
        clearInterval(timerVar); // stop timer
    }
}

function updateJumbotron() {
    document.querySelector(".jumbotron > h1").textContent = "Aktuell spelare må vara " +
    ((oGameData.currentPlayer == "X") ? oGameData.nickNamePlayerOne : oGameData.nickNamePlayerTwo) +
    " (" + oGameData.currentPlayer + ")"; // update jumbotron
}

function updateCountdown() {
    document.querySelector("#errorMsg").textContent = "Du har " +
                ((maxTime - centisecondsElapsed)/10).toFixed(1) + " sekunder på dig att göra ett drag!";
}

function resetGame() {
    document.querySelector("#divInForm").className = "mt-5 row"; // show form
    document.querySelector("#gameArea").className = "d-none"; // hide game area
    oGameData.initGlobalObject(); // fully reset game things
    document.querySelector(".jumbotron > h1").textContent = "TicTacToe"; // reset jumbotron
    document.querySelector("#errorMsg").textContent = "Fyll i nicknames samt färg och börja spela!";
    centisecondsElapsed = 0;
}