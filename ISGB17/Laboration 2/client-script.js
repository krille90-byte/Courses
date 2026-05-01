"use strict";

let socket = io();

window.addEventListener("load", ()=>{
    let buttons = document.querySelectorAll('.btn');
    buttons.forEach((button) => {
        button.addEventListener("click", sendMessage);
    });
});

function sendMessage(e) {
    e.preventDefault();
    let msgBox = document.querySelector("#msg");
    let sendbutton = document.querySelector(".btn");
    sendbutton.textContent = "Skriv inlägg";
    try {
        if(msgBox.value.length <= 2)
            throw new Error("Message too short");
    } catch(e) {
        sendbutton.textContent = e.message;
        return;
    }
    socket.emit("newMessage", msgBox.value);
    msgBox.value = ""; // clear text box
}

socket.on("dataFromServer", function(data) {
    let flow = document.querySelector("#flow");
    let p = document.createElement("p");
    let strong = document.createElement("strong");
    strong.append(document.createTextNode(data.nickname));
    p.append(document.createTextNode(data.timestamp + " "));
    p.append(strong);
    p.append(document.createTextNode(": " + data.msg));
    p.setAttribute("style", "margin: 0");
    flow.append(p);
});