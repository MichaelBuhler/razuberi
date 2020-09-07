
printHelloWorldBang()

function printHelloWorldBang () {

  function printHello () {
    function consoleLog (str) {
      print(str)
    }
    consoleLog('Hello')
  }

  function printWorld () {
    (function (str) {
      print(str)
    })('World')
  }

  function printBang () {
    (() => {
      print('!')
    })()
  }

  printHello()
  printWorld()
  printBang()

  function print (str) {
    console.log(str)
  }
}
