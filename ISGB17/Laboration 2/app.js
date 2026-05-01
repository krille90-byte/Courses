"use strict";

const fs = require("fs");
const express = require("express");
const jspain = require("jsdom");
const kaka = require("cookie-parser");
let app = express();

const http = require('http').createServer(app);
const io = require('socket.io')(http);

app.use(express.urlencoded({extended : true})); // bodyparser
app.use(kaka()); // cookie-parser
http.listen(1770); // port 1770

app.get("/", function(req, res) {
    if(req.cookies.nickname === undefined)
        res.sendFile(__dirname + "/loggain.html");
    else
        res.sendFile(__dirname + "/index.html");
});

app.post("/", function(req, res) {
    if(!(req.body.nickname.length <= 3))
        res.cookie("nickname", req.body.nickname, {maxAge: 1000*60*60*24}); // set cookie with nickname
    res.redirect("/");
});

app.all("*", function(req, res) { // for everything else, send the file
    res.sendFile(__dirname + req.url);
});

io.on("connection", function(socket) {
    let cookieString = socket.handshake.headers.cookie; // vem skickade?
    cookieString = cookieString.replace("%20", " "); // thanks cookies
    socket.on("newMessage", function(message) { // servern fick ett msg
        io.emit("dataFromServer", {"nickname": cookieString.substring("nickname=".length), "msg": message, "timestamp": new Date().toLocaleTimeString("sv-SE")}); // emittar till klienterna att servern fick ett msg
    });
});