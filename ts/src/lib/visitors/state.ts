
export class RazuberiTraversalState {
  private countsByCppFunctionName: Record<string, number> = {}

  public generateUniqueCppFunctionName(baseName: string): string {
    if (this.countsByCppFunctionName[baseName] === undefined) {
      this.countsByCppFunctionName[baseName] = 0
    }
    this.countsByCppFunctionName[baseName] += 1
    const count = this.countsByCppFunctionName[baseName]
    return baseName + '_' + count
  }
}
