def solve(nums, start, end):
    # actual solve mechanism
    return nums[start][1] if start == end else (solve(nums, start, end-1)-solve(nums, start+1, end)) / (nums[start][0]-nums[end][0])

def get_equation(nums):
    # solve mechanism
    size, res = len(nums), []
    for index in range(0, size):
        res.append(solve(nums, 0, size-index-1))
        nums = nums[:-1]
        for i in range(0, len(nums)):
            nums[i][1] = nums[i][1] - res[index] * (nums[i][0] ** (size-index-1))
    return res

def result_to_string(res, total_known):
    s = ''
    for i in range(0, len(res)):
        res[i] = round(res[i], 4)
        if res[i]:
            p = total_known - i - 1
            if not p:
                if res[i] > 0:
                    s += "+"
                ss = str(res[i])
                s += ss[:-2] if ss.endswith('.0') else ss
            else:
                if res[i] > 0:
                    s += "+"
                if res[i] == -1:
                    s += "-"
                elif res[i] != 1:
                    ss = str(res[i])
                    s += ss[:-2] if ss.endswith('.0') else ss
                s += "x"
                if p != 1:
                    s += "^" + str(p)
    if s.startswith('+'):
        s = s[1:]
    if not s:
        s = '0'
    return s

def want_num(qs, cond_out=None, error='Invalid'):
    while True:
        try:
            i = float(input(qs))
        except ValueError:
            print('[!] - Invalid')
        else:
            if not cond_out or i not in cond_out:
                return i
            print('[!] - ', error)

def start():
    # Getting Data
    print('\n[+] - Assume: y = polynomial equation of x.')
    print('\n[+] - Get your inputs(x) and outputs(y) ready!')
    nums, total_known = [], 0
    while total_known < 1:
        total_known = int(want_num('[?] - How much outputs(y) you know? --> '))
    print('[+] - Type the value of x and y one by one\n')
    for _ in range(0, total_known):
        nums.append([want_num('[?] - value of x --> ', cond_out=[i[0] for i in nums], error='Duplicate'), want_num('[?] - value of y --> ')])
        print()
    print('[+] - Got it -->', nums, '\n[+] - Making Function ...')
    
    # finding equation
    res = get_equation(nums)

    # visualize
    print("\n[!] - Data table :", res)
    print('[!] - Success  >> ', result_to_string(res, total_known))

if __name__ == '__main__':
    print('\n\t++++++++++++++++++++++++++++++++++++')
    print('\t+++  Polynomial Equation Finder  +++')
    print('\t+++    By Nayeem @codernayeem    +++')
    print('\t++++++++++++++++++++++++++++++++++++')
    while True:
        start()
        if input("\nEnter 'r' to restart or anything to exit > ").strip().lower() != 'r':
            break
    print('\n\t+++       THANKS FOR USING       +++\n')
