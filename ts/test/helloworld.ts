(function () {
  configure()
  var john = instantiate()
  print()

  function print () {
    console.log(john)
  }
})()

function instantiate () {
  var p =  new Person('John', 'Doe')
  return p
}

function configure () {
  Person.prototype.toString = function () {
    return 'Person: ' + this.firstName + ' ' + this.lastName
  }
}

function Person (firstName, lastName) {
  this.firstName = firstName;
  this.lastName = lastName;
}
