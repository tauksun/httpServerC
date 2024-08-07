console.log("I am from index.js. He Ha :)");
function checkMyHealth() {
  const xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      console.log(xhttp.responseText);
      document.getElementById("healthStatus").innerText = xhttp.responseText;
    }
  };
  xhttp.open("GET", "/health", true);
  xhttp.send();
}
