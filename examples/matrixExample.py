import example
import numpy

a = example.Matrix([[]])
print(a.toString())

a = example.Matrix([[5], [], [1, 3, 5], []])
print(a.toString())

b = example.Matrix(3, 2, 1)
c = b + 1
print(c.toString())
c = c.scalarAdd(1)
print(c.toString())

c = b - 1
print(c.toString())
c = c.scalarSubtract(1)
print(c.toString())

c = b * 3
print(c.toString())
c = c.scalarMultiply(3)
print(c.toString())

a = example.Matrix([[2, 3], [4, 23]])
b = example.Matrix([[1, 9], [13, 7]])
c = a + b
print(c.toString())
c = a.addMatrix(b)
print(c.toString())

c = a.multiplyMatrix(b)
print(c.toString())
c = a * b
print(c.toString())
c = example.multiplyMatrixMatrix([[2, 3], [4, 23]], [[1, 9], [13, 7]])
print(c)

c = a - b
print(c.toString())
c = a.subtractMatrix(b)
print(c.toString())

c = a * b
print(c.toString())
a *= b
print(a.toString())

a = example.Matrix(5, 5, 1)
print(a.toString())

print(a[0])
a[0] = [1, 2, 3, 4, 5]
# a[1][1] = 2

print(a.toString())