eps = 0.001

def line ( point_a, point_b ):
    if ( point_a[0]+eps > point_b[0] ):
        point_a,point_b = point_b,point_a
    elif ( point_a[1]+eps > point_b[1] ):
        point_a,point_b = point_b,point_a

    a = float ( ( point_b[1] - point_a[1] ) )
    b = float ( -( point_b[0] - point_a[0] ) )
    c = float ( -a*point_a[0]-b*point_a[1] )
    d = ( a*a + b*b ) ** 0.5
    
    a /= d; b /= d; c /= d;

    if ( abs ( a ) <= eps ):
        a = 0.0
    if ( abs ( b ) <= eps ):
        b = 0.0
    if ( abs ( c ) <= eps ):
        c = 0.0

    return ( a, b, c, ( point_a, point_b ) )

def online ( point, line ):
    delta_x = float ( line[3][1][0] - line[3][0][0] )
    delta_y = float ( line[3][1][1] - line[3][0][1] )
    
    tx = 0.0; ty = 0.0
    if ( abs(delta_x)>=eps ):
        tx = ( point[0] - line[3][0][0] ) / delta_x
    if ( abs(delta_y)>=eps ):
        ty = ( point[1] - line[3][0][1] ) / delta_y

    return ( tx >= -eps and tx <= 1+eps and ty >= -eps and ty <= 1+eps )


def intersect ( line_a, line_b ):

    if abs ( ( line_a[0]*line_b[1] - line_b[0]*line_a[1] ) ) <= eps:
        return ( False, ( 0, 0 ) )

    x = float ( -( line_a[2]*line_b[1] - line_b[2]*line_a[1] )/( line_a[0]*line_b[1] - line_b[0]*line_a[1] ) )
    y = float ( -( line_a[0]*line_b[2] - line_b[0]*line_a[2] )/( line_a[0]*line_b[1] - line_b[0]*line_a[1] ) )

    if online ( ( x, y ), line_a ) and online ( ( x, y ), line_b ):
        return ( True, ( x, y ) )
    return ( False, ( x, y ) )


def area ( polygon ):
    result = 0.0

    for i in range ( 0, len ( polygon )-1 ):
        result += polygon[i][0] * polygon[i+1][1] - polygon[i+1][0] * polygon[i][1]
    result += polygon[-1][0] * polygon[0][1] - polygon[-1][1] * polygon[0][0]

    return abs(result)*0.5

def cow ( point_a, point_b, point_c ):
    return abs((point_b[0]-point_a[0])*(point_c[1]-point_a[1]) - (point_b[1]-point_a[1])*(point_c[0]-point_a[0]) ) <= eps

def ccw ( point_a, point_b, point_c ):
    return (point_b[0]-point_a[0])*(point_c[1]-point_a[1]) - (point_b[1]-point_a[1])*(point_c[0]-point_a[0]) >= -eps

def eq ( point_a, point_b ):
    return abs ( point_b[0]-point_a[0] ) <= eps and abs ( point_b[1]-point_a[1] ) <= eps

def belongs ( point, polygon ):
    counter = 0

    for i in range ( 0, len ( polygon )-1 ):
        if eq ( point, polygon[i] ) or eq ( point, polygon[i] ):
            return True
        
        point_a = polygon[i]
        point_b = polygon[i+1]
        
        if point_a[1] > point_b[1]:
            point_a,point_b = point_b,point_a
        
        if abs ( point_a[1]-point_b[1] ) <= eps:
            if point_a[0] > point_b[0]:
                point_a,point_b = point_b,point_a
            if abs ( point[1]-point_a[1] ) <= eps and point[0]+eps >= point_a[0] and point[0]-eps <= point_b[0]:
                return True
            continue

        if point[1]+eps >= point_a[1] and point[1]-eps <= point_b[1]:
            if cow ( point_a, point_b, point ):
                return True
            if abs ( point[1]-point_b[1] ) <= eps and point[0] < point_b[0]:
                counter += 1
                continue
            if abs ( point[1]-point_a[1] ) <= eps and point[0] < point_a[0]:
                continue

            if ccw ( point_a, point_b, point ) and ( point_a[0]>point[0] or point_b[0]>point[0] ):
                counter += 1
    
    return (counter&1)

def fl ( p ):
    return ( float ( p[0] ), float ( p[1] ) )

def minority_shape_intersect ( polygon_a, polygon_b ):
    map ( fl, polygon_a )
    map ( fl, polygon_b )

    polygon_a.append ( polygon_a[0] )
    polygon_b.append ( polygon_b[0] )

    polygon = []
    polygon.extend ( polygon_a )
    polygon.extend ( polygon_b )

    for i in range ( 0, len ( polygon_a )-1 ):
        line_a = line ( polygon_a[i], polygon_a[i+1] )
        for j in range ( 0, len ( polygon_b )-1 ):
            line_b = line ( polygon_b[j], polygon_b[j+1] )
            intersection_point = intersect ( line_a, line_b )
            if intersection_point[0] == True:
                polygon.append ( intersection_point[1] )
      
    polygon.sort (); i = 0
    while ( i < len ( polygon )-1 ):
        if ( abs ( polygon[i][0]-polygon[i+1][0] ) <= eps and abs ( polygon[i][1]-polygon[i+1][1] ) <= eps ):
            del polygon[i]
            i = 0
        else:
            i += 1

    final = []
    for i in range ( 0, len ( polygon ) ):
        ra = belongs ( polygon[i], polygon_a ) 
        rb = belongs ( polygon[i], polygon_b )
        
        if ra and rb:
            final.append ( polygon[i] )
    
    return final 

