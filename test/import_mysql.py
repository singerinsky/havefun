import MySQLdb
import random

try:
    conn=MySQLdb.connect(host='localhost',user='root',passwd='firefly',db='gl',port=3306)

    cur=conn.cursor()
    name =['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u']
    index =0;
    for i in range(1,1000000):
        rand_name = random.sample(name,10)
        sql = "insert into role (name) values('%s');"%"".join(rand_name)
    #    print sql
        index = index + 1
        cur.execute(sql)
        if index%1000 == 0:
            print index
            conn.commit()
    cur.close()
    conn.close()
except MySQLdb.Error,e:
    print "Mysql Error %d: %s" % (e.args[0], e.args[1])
