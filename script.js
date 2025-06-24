const quotes = [
  "Follow the Reaper ⚰️",
  "Hate Crew Deathroll 💀",
  "Angels Don’t Kill ☠️",
  "Silent Night, Bodom Night 🌙",
  "Sixpounder 🩸",
  "Every Time I Die 🎸"
];

function generateQuote() {
  const quote = quotes[Math.floor(Math.random() * quotes.length)];
  document.getElementById("quoteBox").innerText = quote;
}
