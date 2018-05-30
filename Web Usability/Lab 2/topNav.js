function toggleOn() {
  	document.getElementById("myNav").style.height = "50%";
  	document.getElementById("navOn").style.display = "none";
    document.getElementById("navOff").style.display = "block";
}

function toggleOff() {
    document.getElementById("myNav").style.height = "0%";
    document.getElementById("navOff").style.display = "none";
    document.getElementById("navOn").style.display = "block";
}

window.onclick = function(event) {
  if (!event.target.matches('.navToggle') && document.getElementById("navOn").style.display == "none") {
  	document.getElementById("myNav").style.height = "0%";
  	document.getElementById("navOff").style.display = "none";
    document.getElementById("navOn").style.display = "block";
  }
}