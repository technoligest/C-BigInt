
def IntToVector(num):

  result = []
  while num>0:
    result.append(num&18446744073709551615);
    num>>=64;
  return result;



def VectorToInt(num):
  result = 0
  for numSection,sectionPostion in zip(num,range(len(num))):
    for exponent in range(63,-1,-1):
      if numSection>=2**exponent:
        result+=2**(exponent+64*sectionPostion)
        numSection-=2**exponent
  return result
