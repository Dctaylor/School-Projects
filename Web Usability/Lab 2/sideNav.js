function toggleOn() {
  	document.getElementById("myNav").style.width = "40%";
  	document.getElementById("navOn").style.display = "none";
}

function toggleOff() {
    document.getElementById("myNav").style.width = "0%";
    document.getElementById("navOn").style.display = "block";
}

window.onclick = function(event) {
  if (!event.target.matches('.navToggle') && document.getElementById("navOn").style.display == "none") {
  	document.getElementById("myNav").style.width = "0%";
    document.getElementById("navOn").style.display = "block";
  }
}