"""
    Done
"""

def activity_selector(selected,name,s,f,k,n):
    m = k+1
    while (m <= n) and (s[m] < f[k]):
        m = m + 1
    if m <= n:
        selected.append(name[m])
        return activity_selector(selected,name,s,f,m,n)
    else:
        return []

if __name__ == "__main__" :

    activity_dic = {
        'a1': [3, 5],
        'a2': [0, 6],
        'a3': [1, 4],
        'a4': [5, 7],
        'a5': [3, 9],
        'a6': [6, 10],
        'a7': [12, 16],
        'a8': [2, 14],
        'a9': [8, 11],
        'a10': [8,12],
        'a11': [5,9]
    }

    sort_activity  = {k:v for k,v in sorted(activity_dic.items(), key=lambda item:item[1][1])}

    print(sort_activity)

    name = list(sort_activity.keys())
    s = [v[0] for v in sort_activity.values()]
    f = [v[1] for v in sort_activity.values()]

    name.insert(0,'a0')
    s.insert(0,0)
    f.insert(0,0)

    # quick.quicksort(f,0,len(f)-1)

    print(f"names    : {name}")
    print(f"starting : {s}")
    print(f"finish   : {f}")

    k = 0
    n = len(name) - 1

    selected = []

    _ = activity_selector(selected,name,s,f,k,n)

    print(f"selected : {selected}")
