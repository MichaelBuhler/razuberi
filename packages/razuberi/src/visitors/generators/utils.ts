
export const indent = (str: string, depth: number = 2) : string => {
  const padding = ' '.repeat(depth)
  return padding + str.replace(/\n/g, `\n${padding}`)
}
