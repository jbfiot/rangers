#!coding: utf-8
import random

"""
    Script pour génération automatique des fichiers:
        * .SIFT:                liste des points SIFT
        *  database.data :      liste des index des SIFTS
        * sifts_files.data :    liste des fichiers .SIFT utilisés
"""

NB_IMAGES = 10
NB_SIFTS_INF = 10
NB_SIFTS_SUP = 20


def random_vector(n):
    l=[]
    for i in xrange(n):
        l.append(`random.randrange(0, 100)`)
    return l


g=open('database.data', 'w')
h=open('sifts_files.data', 'w')

START = True

for i in xrange(NB_IMAGES):
    
    nb_sifts_in_image = random.randrange(NB_SIFTS_INF,NB_SIFTS_SUP)
    
    
    
    f=open('image'+str(i)+'.SIFT', 'w')
    f.write('../Samples/image'+str(i)+'.jpg\t640\t480\ttags lol vacances\n')
    

    for j in xrange(nb_sifts_in_image):
        x = random.randrange(0, 640)
        y = random.randrange(0, 480)
        
        if START:
            f.write(('%s\t%s\t'%(x, y))+'\t'.join(random_vector(128)))
            g.write('../Samples/image'+str(i)+'.SIFT\t'+str(j+1))
            START = False
        else:
            f.write(('\n%s\t%s\t'%(x, y))+'\t'.join(random_vector(128)))
            g.write('\n../Samples/image'+str(i)+'.SIFT\t'+str(j+1))

    f.close()
    
    h.write('../Samples/image'+str(i)+'.SIFT\n')
    

g.close()
h.close()    


