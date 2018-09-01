import random
import sys
def generateMatrix(dim, qty, name, g = lambda x, y : x != y ):
    if qty > dim*dim:
        raise ValueError('invalid input. More links than possible for the supplied matrix.')
    s = str(dim)+"\n"+str(qty)+"\n"
    pairs = [(i,j) for i in range(1,dim+1) for j in range(1,dim+1) if g(i,j)]
    used_pairs = random.sample(pairs, qty)
    for p,q in used_pairs:
	s+= str(p)+" "+str(q)+"\n"
    with open(name, 'w') as f:
	    f.write(s)


#dim, qty, name
def main(args):
    try:
        generateMatrix(int(args[0]),int(args[1]),args[2])	
    except:
        raise ValueError('invalid input. terminating. Correct usage should be: generateMatrix.py <DIMENSION> <QUANTITY OF LINKS> <OUTPUT FILE NAME>.')
args = sys.argv[1:]
main(args)
