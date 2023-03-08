function pushMultiplySum(vec,x) {
    vec.push(x)
    return vec.map(i => i * 2).reduce((a, b) => a + b)
}