interface Person {
  firstName: string
  lastName: string
  new(firstName: string, lastName: string)
  toString(): string
}

(function () {
  configure()
  john || console.log("john is not defined")
  var john = instantiate()
  john && console.log("john is now defined")
  print()
  check(john)
  defenestrate()

  function print () {
    console.log(john)
  }
})()

function instantiate () : Person {
  var p =  new Person('John', 'Doe')
  return p
}

function configure () {
  Person.prototype.toString = function (this: Person) : string {
    return 'Person: ' + this.firstName + ' ' + this.lastName
  }
}

function check (person: Person) {
  console.log('person.firstName == \\"Doe\\" =>', person.firstName == "Doe")
  console.log('person.fake === undefined =>', undefined === person.fake)
  console.log('undefined !== null =>', undefined !== null)
}

function defenestrate () {
  throw new Person("Alice", "Bob")
}

function Person (this: Person, firstName: string, lastName: string) {
  this.firstName = firstName;
  this.lastName = lastName;
}
