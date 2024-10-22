document.addEventListener("DOMContentLoaded", function () {
    const result = document.getElementById("res");
    const buttons = document.querySelectorAll ("button");
  
    function clearresult() {
      result.innerHTML = "Result";
    }
  
    function addToresult(value) {
        result.innerHTML += value;
    }
  
  
    buttons.forEach((button) => {
      button.addEventListener("click", function () {
        if (result.innerHTML === "Result" || result.innerHTML === "Error" || result.innerHTML === "Infinity" || result.innerHTML === "-Infinity")
          result.innerHTML="";
        const buttonText = button.value;
        if (button.value === "=") {
          try {
            const input = result.innerHTML;
            result.innerHTML = eval(input);
          } catch (error) {
            result.innerHTML = "Error";
          }
        } else if (buttonText === "c") {
          clearresult();
        } else {
          addToresult(buttonText);
        }
      });
    });
  });
  