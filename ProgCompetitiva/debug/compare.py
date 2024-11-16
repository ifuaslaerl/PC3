" Fofoca gamer. "
user = open("debug/user_output.txt","r", encoding="utf-8")
test = open("debug/test_output.txt","r", encoding="utf-8")

for test_line in test:
    user_line = user.readline().split()
    test_line = test_line.split()

    for gab, user_out  in zip(test_line, user_line):
        if gab != user_out :
            print(gab)
            print(user_out)
            break
