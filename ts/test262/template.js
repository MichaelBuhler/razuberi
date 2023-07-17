/*
 * This is the test template file. It is as small as possible.
 */

import test from 'ava'
import { globSync } from 'glob'

import { runner } from '__RELATIVE_PATH_TO_RUNNER_JS__'
import { loadTestResults, TestResult } from '__RELATIVE_PATH_TO_SNAPSHOT_JS__'

const testFolder = '__TEST_FOLDER__'

const testFiles = globSync(`${testFolder}/*.js`, {
  cwd: '__TEST262_DIR__/test',
  ignore: '**/*FIXTURE*',
  nodir: true,
}).sort()

const expectedTestResults = loadTestResults(testFolder)

for (const testFile of testFiles) {
  if (expectedTestResults[testFile] === TestResult.FAIL) {
    test.serial.failing(runner, testFile)
  } else {
    test.serial(runner, testFile)
  }
}
