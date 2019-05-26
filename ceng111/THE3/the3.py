def ok ( corpus, V ):
    s = []
    s.extend ( V )
    for j in range ( 0, len ( V ) ):
        cV = ""
        for i in range ( 0, len ( V ) ):
            cV += ( V[i][j] )
        s.append ( cV )
    if len ( s ) != len ( list ( set ( s ) ) ): return False
    for i in s:
        if i not in corpus:
            return False
    return True
def solve ( corpus, vv, N ):
    for j in range ( 0, N ):
        s = ""
        flag = 0
        for i in range ( 0, len ( vv ) ):
            s += vv[i][j]
        for i in range ( 0, len ( corpus ) ):
            if corpus[i][:len(vv)] == s:
                flag = 1
                break
        if flag == 0: return False
    if len ( vv ) == N:
        if ok ( corpus, vv ): return vv
        else: return False
    for i in corpus:
        if i not in vv:
            vv.append ( i )
            ret = solve ( corpus, vv, N )
            if ret != False:
                return ret
            vv.pop ()
    return False
def place_words ( corpus ):
    for i in range ( 0, len ( corpus ) ):
        corpus[i] = corpus[i].upper ()
    if corpus == []: return False
    return solve ( corpus, [], len ( corpus[0] ) )
