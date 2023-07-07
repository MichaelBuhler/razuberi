(function () {
  configure()
  var john = instantiate()
  print()

  function print () {
    console.log(john)
  }
})()

function instantiate () {
  return new Person()
}

function configure () {
  Person.prototype.toString = function () {
    return 'Person: ' + this.name
  }
}

function Person () {
  this.name = "John Doe";
}
