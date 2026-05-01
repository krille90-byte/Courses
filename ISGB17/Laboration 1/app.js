// Grupp 35: Arvid Rimmerfors, Christer Linde, Martin Persson

"use strict";

// Vi förstod ej användningen av bodyparser (som också är deprecated) med express, och valde att istället göra vår egen server.
const http = require("http");
const fs = require("fs");
const path = require("path");
const jspain = require("jsdom");
var bp = require("./blogPosts.js");

http.createServer(function(req, res) {
    // Handle POST
    if(req.method == "POST") {
        req.on("data", bonk => {
            let prettyData = new URLSearchParams(bonk.toString());
            let subject = prettyData.get("subject");
            let msg = prettyData.get("msgbody");
            
            try {
                if (subject.length < 2)
                    throw new Error("Ditt &auml;mne &auml;r f&ouml;r kort");
                if (msg.length < 4)
                    throw new Error("Ditt inl&auml;gg är f&ouml;r kort");
            }
            catch(e) {
                res.writeHead(200, { "Content-Type" : "text/html" });
                res.end(e.message);
                return;
            }
            bp.blogPosts.push({
                nickName: prettyData.get("nickname"),
                msgSubject: subject,
                timeStamp: new Date().toLocaleDateString("sv-SE"),
                msgBody: msg
            });
        });
        req.on("end", () => {
            res.writeHead(302, { // send the user back home
                "Location": "/"
            });
            res.end();
        });
        return; // don't continue 
    }

    // Handle GET
    let filePath = (req.url === "/") ? "index.html" : req.url.substring(1); // if(thing) ? true-stuff : false-stuff;
    let extName = path.extname(filePath);
    if(extName == "")
        filePath += ".html";

    fs.readFile(filePath, function(err, data) {
        if(err) {
            res.writeHead(404, { "Content-Type" : "text/html" });
            res.end();
        } else {
            let contentType = "text/html";
            switch (extName) {
                case ".css":
                    contentType = "text/css";
                    break;
                case ".js":
                    contentType = "text/javascript";
                    break;
                case ".json":
                    contentType = "application/json";
                    break;
                case ".png":
                    contentType = "image/png";
                    break;
                case ".jpg":
                    contentType = "image/jpg";
                    break;
                case ".svg":
                    contentType = "image/svg+xml";
                    break;
            }
            res.writeHead(200, { "Content-Type" : contentType });

            switch(filePath) {
                case "index.html": // if we're serving the index
                    let serverDOM = new jspain.JSDOM(data);
                    let doc = serverDOM.window.document;
                    let theSection = doc.querySelector("section");
                    for(let i = 0; i < bp.blogPosts.length; i++) {
                        // Create a div
                        let div = doc.createElement("div");
                        div.setAttribute("style", "background-color: #e9ecef; padding: 12px; border-radius: 10px; margin-bottom: 15px;");

                        // Title
                        let title = doc.createElement("h1");
                        title.append(doc.createTextNode(bp.blogPosts[i].msgSubject));
                        title.setAttribute("style", "margin-bottom: 0;");
                        div.append(title);

                        // Subtitle with date and name 
                        let subtitle = doc.createElement("p");
                        subtitle.setAttribute("style", "font-size: 11pt; color: grey; margin: 0 0 2px 0;");
                        subtitle.append(doc.createTextNode("Skrivet av " + bp.blogPosts[i].nickName + " på " + bp.blogPosts[i].timeStamp + "."));
                        div.append(subtitle);

                        // Message content
                        let description = doc.createElement("p");
                        description.append(doc.createTextNode(bp.blogPosts[i].msgBody));
                        div.append(description);
                        
                        theSection.append(div);
                    }
                    
                    res.write(serverDOM.serialize());
                    res.end();
                    break;
                default: // serve resources
                    let content = fs.readFileSync(filePath).toString();
                    res.write(content);
                    res.end();
                    break;
            }
        }
    });
}).listen(1770); // port 1770