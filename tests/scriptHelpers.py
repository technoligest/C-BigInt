
def intToVector(num):

  result = []
  while num>0:
    result.append(num&18446744073709551615);
    num>>=64;
  return result;



def vectorToInt(num):
  result = 0
  for numSection,sectionPostion in zip(num,range(len(num))):
    for exponent in range(63,-1,-1):
      if numSection>=2**exponent:
        result+=2**(exponent+64*sectionPostion)
        numSection-=2**exponent
  return result


print(intToVector(123432542352524323892589243))

num1 = vectorToInt([18446744073709551615,18446744073709551615,18446744073709551615, 3124, 342432, 0, 18446744073709551615,18446744073709551615,18446744073709551615,0,1,1,0])
num2 = vectorToInt([1])
print(num1);
print(num2)
print(num1+num2)


num3 = vectorToInt([0,0,0,0,0,0,1,0,0,0,17])

print(num3)

num4 = vectorToInt([321432,31234,18446744073709551615,134,19834,1456])
num5 = vectorToInt([0,0,18446744073709551615,134,19834,1456])

print(num4)
print(num5)
print(num4-num5)

num6 = vectorToInt([145,21,0,0,0,0,956,12,0,0,0,200])
num7 = vectorToInt([45,97234,0,0,0,0,14,95])
print(num6)
print(num7)
print(num6-num7)
print(intToVector(num6-num7))