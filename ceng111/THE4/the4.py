p =  {}
h =  {}
nh = {}
ps = {}
tree_height = 0


def help_ben_solo ( tree, threshold ):
    tree_height = build_tree_p ( tree, [] )
    build_tree_h ( tuple(tree[:2]), tree_height ) 

    # Constraint 1b
    for i in h:
        h[i] = sorted ( h[i], key=lambda x: x[1] )
    for i in h:
        for j in h:
            while j < i and h[i][0][1] < h[j][-1][1]:
                h[i][0],h[j][-1] = h[j][-1],h[i][0]
                p[h[i][0]],p[h[j][-1]] = p[h[j][-1]],p[h[i][0]]
                
                # /root change
                if h[i][0][0] == tree[0]:
                    tree[0] = h[j][-1][0]
                    tree[1] = h[j][-1][1]
                elif h[j][-1][0] == tree[0]:
                    tree[0] = h[i][0][0]
                    tree[1] = h[i][0][1]
                # root change/

                # /children exchange
                for x in p:
                    if p[x] == h[i][0]:
                        p[x] = ( '+' + h[j][-1][0], h[j][-1][1] )
                for x in p:
                    if p[x] == h[j][-1]:
                        p[x] = h[i][0]
                    elif p[x] != [] and p[x][0] == str('+' + h[j][-1][0]):
                        p[x] = h[j][-1]
                # children exchange/

                nh[h[i][0]],nh[h[j][-1]] = nh[h[j][-1]],nh[h[i][0]]

                h[i] = sorted ( h[i], key=lambda x: x[1] )
                h[j] = sorted ( h[j], key=lambda x: x[1] ) 
             
    #print "p:", p
    #print
    #print "nh:", nh
    #print
    #print "h:", h
    # Constraint 1e
    #return create_nested_list_tree_from_p ( tuple(tree[:2]) )
    build_tree_ps ( tuple(tree[:2]), [] )
    for i in ps:
        ps[i].reverse ()
    ###############################################################################
    # Constraint 2b
    #print "ps:", ps
    #helper = sorted ( h.keys (), reverse=True )
    for i in range ( 1, min(threshold,tree_height) ):
        j = 0
        while j < len(h[i]):
            #print "h[i][j]", h[i][j]
            for k in ps[h[i][j]]:
                if nh[k] > threshold:
                    #print k
                    #print "sum(k)", sum(k)
                    if sum(k)+h[i][j][1] <= k[1]:
                        ok = 1

                        ############check for constraint1##############
                        if nh[k]-2 in h.keys () and nh[k]-2 >= threshold:
                            for d in h[nh[k]-2]:
                                #print "d=", d
                                if d[1] > h[i][j][1]:
                                    ok = 0
                                    break
                        for d in h[nh[k]]:
                            if d[1] < h[i][j][1]:
                                ok = 0
                                break
                        #################checked######################
                        
                        if ok:
                            #print "ok"
                            #print k
                            #print h[i][j]
                            h[nh[k]-1].append ( h[i][j] )
                            nh[h[i][j]] = nh[k]-1
                            p[h[i][j]] = k
                            del h[i][j]
                            j -= 1
                            
                            build_tree_ps ( tuple(tree[:2]), [] )
                            for d in ps:
                                ps[d].reverse ()
                            break
            j += 1

    rem = []
    helper = p.keys ()
    for i in helper:
        if nh[i] < threshold and threshold <= tree_height:
            p.pop(i, None)
            rem.append ( i[0] )
    # Constraint 2e
    return ( create_nested_list_tree_from_p ( tuple(tree[:2]) ), rem )

##########################################
def build_tree_h ( u, height ):
    if height not in h.keys ():
        h[height] = []
    h[height].append ( u )
    nh[u] = height
    for i in p:
        if p[i] == u:
            build_tree_h ( i, height-1 )

def build_tree_ps ( u, path ):
    ps[u] = path
    for i in p:
        if p[i] == u:
            build_tree_ps ( i, path+[u] )

def build_tree_p ( tree, prev ):
    p[tuple(tree[:2])] = prev
    height = 1
    for i in tree:
        if type(i) == list:
            height = max ( height, build_tree_p ( i, tuple(tree[:2]) )+1 )
    return height
##########################################

def sum ( node ):
    ans = 0
    for i in p:
        if p[i] == node:
            ans += i[1]
    return ans

def create_nested_list_tree_from_p ( u ):
    ans = [u[0], u[1]]
    for i in p:
        if p[i] == u:
            ans.append ( create_nested_list_tree_from_p ( i ) )
    return ans


"""
H = ['A', 60, ['B', 10, ['C', 4, ['D', 2], ['E', 3]], ['F', 3, ['G', 1, ['H', 1], ['I', 1]], ['J', 2]]], ['K', 1, ['L', 3], ['M', 4]], ['N', 20, ['P', 6, ['Q', 5, ['R', 2, ['S', 3], ['T', 4], ['U', 5]]]]], ['O', 20]]
T = 4
print help_ben_solo ( H, T )

print help_ben_solo ( ['A', 29, ['B', 15, ['E', 3] ], ['C', 2, ['F', 1, ['J', 1], ['K', 7, ['N', 30], ['O', 2]]]], ['D', 5, ['G', 1], ['H', 1], ['I', 4, ['L', 2], ['M', 2, ['P', 1], ['R', 7], ['S', 2]]]]], 4 )
print help_ben_solo( 
        ["Ben Solo", 50, ["Jack", 9, ["Fredo", 2, ["Kyle", 1], ["Luke", 1]], ["Vincenzo", 1], ["Fred", 6, ["Ela", 3], ["Han", 3]]], ["John", 18, ["Rocco", 3], ["Nico", 14]]], 2)
print help_ben_solo ( ['A', 1, \
        ['B', 2,['K', 1], ['M', 1], ['L', 1]], \
        ['C', 7,['D', 14,['G', 1,['H', 1,['J', 1], ['I', 1]]]], ['E', 2], ['F', 1]]], 5 )
"""

