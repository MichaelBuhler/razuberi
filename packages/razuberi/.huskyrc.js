
module.exports = {
  hooks: {
    'pre-commit': 'npm run lint:staged && npm run test'
  }
}
