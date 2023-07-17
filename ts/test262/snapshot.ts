
const path = await import('node:path')

// @ts-ignore
import { load as makeSnapshotManager } from '../node_modules/ava/lib/snapshot-manager.js'
// @ts-ignore
import { snapshotManager as concordanceOptions } from '../node_modules/ava/lib/concordance-options.js'
// @ts-ignore
import concordance from 'concordance'
//@ts-ignore
import { tag as ErrorValue } from '../node_modules/concordance/lib/complexValues/error.js'

const __dirname = path.dirname(import.meta.url.slice(5))

type TestTitle = string
export enum TestResult { PASS, FAIL }

type TestResults = Record<TestTitle, TestResult>

export const loadTestResults = (testFolder: string) : TestResults => {
  const snapshotManager = makeSnapshotManager({
    file: path.join(testFolder, 'index.js'),
    fixedLocation: 'snapshots',
    projectDir: __dirname,
    recordNewSnapshots: false,
    updating: false,
  })
  
  const testResults: TestResults = {}
  for ( const [testTitle, block] of snapshotManager.oldBlocksByTitle.entries() ) {
    const { snapshots: [snapshot] } = block
    const { data: serializedConcordanceData } = snapshot
    const value = concordance.deserialize(serializedConcordanceData, concordanceOptions)
    if (value.tag === ErrorValue) {
      testResults[testTitle] = TestResult.FAIL
    } else {
      testResults[testTitle] = TestResult.PASS
    }
  }

  return testResults
}
