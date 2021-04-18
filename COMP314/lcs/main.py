""" Longest Common Sequence """

def LCS_length(str1,str2) :
    """
        returns length table and
        the Direction table
    """

    m = len(str1) + 1 # Rows from string 1
    n = len(str2) + 1 # Columns form string 2

    len_t = [[0 for i in range(n)] for j in range(m)]
    prev_t= [['-' for i in range(n)] for j in range(m)]

    for i in range(1,m):
        for j in range(1,n):
            x = i-1
            y = j-1
            # print(j)
            if(str1[x] == str2[y]):
                len_t[i][j] = len_t[i-1][j-1] + 1
                prev_t[i][j] = 'd'
            elif(len_t[i-1][j] > len_t[i][j-1]):
                len_t[i][j] = len_t[i-1][j]
                prev_t[i][j] = 'u'
            else:
                len_t[i][j] = len_t[i][j-1]
                prev_t[i][j] = 'b'
            # else:
            # len_t[i][j] = max(len_t[i-1][j],len_t[i][j-1])

    # print(len(len_t))
    # print(len(len_t[0]))
    # return len_t[m-1][n-1]

    return len_t, prev_t

def output_LCS(result,str_1,prev_t,i,j):
    """
        Calculate the LCS using prev_t (Direction Tabel)
        and store it in result
    """
    # result = []
    if(i==0 or j == 0):
        return None
    if prev_t[i][j]=='d':
        output_LCS(result,str_1,prev_t,i-1,j-1)
        result.append(str_1[i-1])
    elif prev_t[i][j]=='u':
        output_LCS(result,str_1,prev_t,i-1,j)
    else:
        output_LCS(result,str_1,prev_t,i,j-1)




if __name__ == "__main__" :

    s1 = "speculate"
    s2 = "splatula"

    m = len(s1) + 1 # Rows from string 1
    n = len(s2) + 1 # Columns form string 2

    len_t, prev_t = LCS_length(s1,s2) # numerical value, direction table

    print("\n Length Table :")

    for i in range(len(len_t)):
        print(len_t[i])

    print()

    print("\n Direction Table :")

    for i in range(len(prev_t)):
        print(prev_t[i])

    print(f"\nFound a LCS of length {len_t[m-1][n-1]}\n")

    result = []
    output_LCS(result,s2,prev_t,m-1,n-1)

    print(f"The LCS of the sequences '{s1}' and '{s2}' is \"{''.join(result)}\"\n")
