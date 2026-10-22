// ITSupport ticket server. Zero dependencies. Run:  node server.js
// Optional: ADMIN_PIN=1234 node server.js   (protects the admin console)
//           PORT=8080 node server.js
"use strict";
const http = require("http"), fs = require("fs"), path = require("path"), crypto = require("crypto");
const PORT = +process.env.PORT || 3000;
const PIN = process.env.ADMIN_PIN || "";
const DIR = __dirname, DB = path.join(DIR, "tickets.json");
const CATS = ["Wi-Fi / Wireless","Network outage","VPN / Access","Email","Phone / Voice","Printer","Other"];
const PRIS = ["Low","Normal","High","Critical"];
const STATUSES = ["Open","In progress","Resolved"];
const FILES = {"/":"index.html","/index.html":"index.html","/admin.html":"admin.html"};
const TYPES = {".html":"text/html; charset=utf-8"};

let tickets = [];
try { tickets = JSON.parse(fs.readFileSync(DB, "utf8")); if (!Array.isArray(tickets)) tickets = []; } catch (e) { tickets = []; }
function save() { const tmp = DB + ".tmp"; fs.writeFileSync(tmp, JSON.stringify(tickets, null, 1)); fs.renameSync(tmp, DB); }
function nextId() { let m = 1000; tickets.forEach(t => { const n = +String(t.id).replace(/\D/g, ""); if (n > m) m = n; }); return "ITS-" + (m + 1); }
const clip = (v, n) => String(v == null ? "" : v).trim().slice(0, n);
function sha(s) { return crypto.createHash("sha256").update(String(s)).digest(); }
function authed(req) { if (!PIN) return true; return crypto.timingSafeEqual(sha(req.headers["x-admin-pin"] || ""), sha(PIN)); }
const hits = new Map();
function limited(ip) { const now = Date.now(), a = (hits.get(ip) || []).filter(t => now - t < 60000); a.push(now); hits.set(ip, a); return a.length > 20; }

function send(res, code, obj) {
  const body = JSON.stringify(obj);
  res.writeHead(code, {"Content-Type":"application/json; charset=utf-8","Cache-Control":"no-store","X-Content-Type-Options":"nosniff"});
  res.end(body);
}
function readBody(req, cb) {
  let data = "", dead = false;
  req.on("data", c => { data += c; if (data.length > 100000 && !dead) { dead = true; req.destroy(); } });
  req.on("end", () => { if (dead) return; try { cb(null, JSON.parse(data || "{}")); } catch (e) { cb(e); } });
}

http.createServer((req, res) => {
  const url = req.url.split("?")[0];
  const ip = req.socket.remoteAddress || "?";

  if (url === "/api/ping") return send(res, 200, {ok: true, pin: !!PIN});

  if (url === "/api/tickets" && req.method === "POST") {
    if (limited(ip)) return send(res, 429, {error: "Too many tickets, slow down."});
    return readBody(req, (err, b) => {
      if (err) return send(res, 400, {error: "Bad JSON"});
      const t = {
        id: nextId(), ts: Date.now(),
        name: clip(b.name, 80), email: clip(b.email, 120),
        cat: CATS.includes(b.cat) ? b.cat : "Other",
        pri: PRIS.includes(b.pri) ? b.pri : "Normal",
        desc: clip(b.desc, 2000), status: "Open"
      };
      if (!t.desc) return send(res, 400, {error: "Description required"});
      tickets.push(t); save();
      send(res, 201, {id: t.id, ts: t.ts});
    });
  }

  if (url.startsWith("/api/tickets")) {
    if (!authed(req)) return send(res, 401, {error: "PIN required"});
    if (url === "/api/tickets" && req.method === "GET") return send(res, 200, tickets);
    const id = decodeURIComponent(url.slice("/api/tickets/".length));
    const t = tickets.find(x => x.id === id);
    if (!t) return send(res, 404, {error: "Not found"});
    if (req.method === "DELETE") { tickets = tickets.filter(x => x !== t); save(); return send(res, 200, {ok: true}); }
    if (req.method === "PATCH") return readBody(req, (err, b) => {
      if (err || !STATUSES.includes(b.status)) return send(res, 400, {error: "Bad status"});
      t.status = b.status; save(); send(res, 200, t);
    });
    return send(res, 405, {error: "Method not allowed"});
  }

  if (req.method === "GET" && FILES[url]) {
    return fs.readFile(path.join(DIR, FILES[url]), (e, d) => {
      if (e) { res.writeHead(404); return res.end("Missing " + FILES[url]); }
      res.writeHead(200, {"Content-Type": TYPES[".html"], "X-Content-Type-Options": "nosniff"});
      res.end(d);
    });
  }
  res.writeHead(404); res.end("Not found");
}).listen(PORT, "0.0.0.0", () => {
  console.log("ITSupport portal:   http://localhost:" + PORT + "/");
  console.log("Staff console:      http://localhost:" + PORT + "/admin.html");
  console.log(PIN ? "Admin PIN is ON." : "WARNING: no ADMIN_PIN set. Anyone who can reach this server can read tickets.");
});