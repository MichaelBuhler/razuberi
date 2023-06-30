
import type { Node } from '@babel/types'

export type Generator<N extends Node> = (node: N) => string
