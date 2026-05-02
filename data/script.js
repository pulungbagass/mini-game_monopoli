function controlLED(state) {
  fetch("/led?state=" + state)
    .then(response => response.text())
    .then(data => {
      document.getElementById("status").innerHTML = "Status: " + data;
    })
    .catch(err => {
      console.error(err);
    });
}