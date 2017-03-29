2017-01-23
初始化一个Git仓库，使用git init命令。

添加文件到Git仓库，分两步：

第一步，使用命令git add <file>，注意，可反复多次使用，添加多个文件；
//出现个警告：http://blog.csdn.net/unityoxb/article/details/20768687

第二步，使用命令git commit，完成。


要随时掌握工作区的状态，使用git status命令。

如果git status告诉你有文件被修改过，用git diff可以查看修改内容。


HEAD指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令git reset --hard commit_id。
在Git中，用HEAD表示当前版本，上一个版本就是HEAD^，上上一个版本就是HEAD^^，当然往上100个版本写100个^比较容易数不过来，所以写成HEAD~100

穿梭前，用git log可以查看提交历史，以便确定要回退到哪个版本。

要重返未来，用git reflog查看命令历史，以便确定要回到未来的哪个版本

版本库  工作区  暂存区（stage）  master  HEAD

理解了Git是如何跟踪修改的，每次修改，如果不add到暂存区，那就不会加入到commit中。

2013-01-24
分支管理
新功能  50%   进度
1、创建与合并分支
分支线，时间线，主分支master    HEAD指针
提交点commit  
创建并切换到创建的分支：git checkout -b dev
创建分支：git branch  dev
切换分支：git checkout  dev
查看当前分支：git branch
*  dev  *表示当前分支

然后添加提交：
git add readme.txt 
git commit -m "branch test"

合并到master分支：
git merge dev
Fast-forward信息，Git告诉我们，这次合并是“快进模式”

合并完成后删除dev分支：
git branch -d dev

2、解决冲突
选择master分支重新打开，修改提交，就能解决？？
还是可以切换其他分支？
当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。
用git log --graph命令可以看到分支合并图。

 git log --graph --pretty=oneline --abbrev-commit

3、分支管理策略
git merge --no-ff -m "merge with no-ff" dev
--no-ff参数，表示禁用Fast forward
合并要创建一个新的commit，所以加上-m参数，把commit描述写进去

4、Bug分支
Git提供了一个stash功能，可以把当前工作现场“储藏”起来，等以后恢复现场后继续工作
git stash


首先确定要在哪个分支上修复bug，假定需要在master分支上修复，就从master创建临时分支
git checkout master
git checkout -b issue-101

git add readme.txt 
git commit -m "fix bug 101"

git checkout master
git branch -d issue-101

git checkout dev

查看工作现场
git stash list

git stash apply恢复，但是恢复后，stash内容并不删除，你需要用git stash drop来删除；

另一种方式是用git stash pop，恢复的同时把stash内容也删了


开发一个新feature，最好新建一个分支；

如果要丢弃一个没有被合并过的分支，可以通过git branch -D <name>强行删除。


查看远程库信息，使用git remote -v；

本地新建的分支如果不推送到远程，对其他人就是不可见的；

从本地推送分支，使用git push origin branch-name，如果推送失败，先用git pull抓取远程的新提交；

在本地创建和远程分支对应的分支，使用git checkout -b branch-name origin/branch-name，本地和远程分支的名称最好一致；

建立本地分支和远程分支的关联，使用git branch --set-upstream branch-name origin/branch-name；

从远程抓取分支，使用git pull，如果有冲突，要先处理冲突。


2017-02-06
1.安装Git
$ git config --global user.name "Your Name"
$ git config --global user.email "email@example.com"

2.创建版本库
创建文件夹（目录）PS：保目录名（包括父目录）不包含中文，进入这个文件夹下；
$ git init   初始化这个文件夹为仓库
隐藏文件：.git目录  ls -ah可查
$ git add readme.txt      把文件添加到仓库
$ git commit -m "wrote a readme file"   文件提交到仓库

3.时光机穿梭
$ git status   时刻掌握仓库当前的状态
$ git diff readme.txt         顾名思义就是查看difference

HEAD指向的版本就是当前版本，因此，Git允许我们在版本的历史之间穿梭，使用命令git reset --hard commit_id。
穿梭前，用git log可以查看提交历史，以便确定要回退到哪个版本。
要重返未来，用git reflog查看命令历史，以便确定要回到未来的哪个版本。

暂存区是Git非常重要的概念，弄明白了暂存区，就弄明白了Git的很多操作到底干了什么

理解了Git是如何跟踪修改的，每次修改，如果不add到暂存区，那就不会加入到commit中

场景1：当你改乱了工作区某个文件的内容，想直接丢弃工作区的修改时，用命令git checkout -- file。
场景2：当你不但改乱了工作区某个文件的内容，还添加到了暂存区时，想丢弃修改，分两步，第一步用命令git reset HEAD file，就回到了场景1，第二步按场景1操作。
场景3：已经提交了不合适的修改到版本库时，想要撤销本次提交，参考版本回退一节，不过前提是没有推送到远程库。

命令git rm用于删除一个文件

查看远程库信息，使用git remote -v
4.远程仓库
2017-02-06
Git远程仓库：GitHub
第1步：注册GitHub账号

第2步：创建SSH Key。
看.ssh目录下是否有id_rsa私钥和id_rsa.pub公钥,有则跳过这一步
否则创建SSH Key：
$ ssh-keygen -t rsa -C "youremail@example.com"

第3步：登录GitHub添加公钥，完成

添加远程库
第一步：在GitHub创建新仓库
第二步：关联远程库
$ git remote add origin git@github.com:michaelliao/learngit.git
第三步：把本地库的所有内容推送到远程库上
$ git push -u origin master
由于远程库是空的，我们第一次推送master分支时，加上了-u参数

从远程库克隆
$ git clone git@github.com:michaelliao/gitskills.git

5.分支管理
创建与合并分支

6.标签管理
命令git tag <name>用于新建一个标签，默认为HEAD，也可以指定一个commit id；
git tag -a <tagname> -m "blablabla..."可以指定标签信息； 用-a指定标签名，-m指定说明文字
git tag -s <tagname> -m "blablabla..."可以用PGP签名标签；
命令git tag可以查看所有标签。
git show <tagname>查看标签信息

命令git push origin <tagname>可以推送一个本地标签；
命令git push origin --tags可以推送全部未推送过的本地标签；
命令git tag -d <tagname>可以删除一个本地标签；
命令git push origin :refs/tags/<tagname>可以删除一个远程标签。

7.使用GitHub
8.自定义Git
9


02-22
git add xx命令可以将xx文件添加到暂存区，如果有很多改动可以通过 git add -A .来一次添加所有改变的文件。
注意 -A 选项后面还有一个句点。 git add -A表示添加所有内容， git add . 表示添加新文件和编辑过的文件不包括删除的文件; git add -u 表示添加编辑或者删除的文件，不包括新添加的文件。