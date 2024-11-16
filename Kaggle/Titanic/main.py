from sklearn import linear_model
from sklearn import preprocessing
from sklearn import neighbors
import shutil
import os
import pandas as pd

shutil.rmtree("resps")
os.makedirs("resps")

data = pd.read_csv("data/train.csv")
test = pd.read_csv("data/test.csv")
asw = pd.read_csv("data/gender_submission.csv")

total = len(asw)

resp = pd.DataFrame()

data = data[['Survived','Pclass', 'Sex', 'Age']]
y = data['Survived']
data = data[['Pclass', 'Sex', 'Age']]
data['Sex'] = data['Sex'].replace('male','-1')
data['Sex'] = data['Sex'].replace('female','1')
data['Age'] = data['Age'].fillna(0)

scaler = preprocessing.RobustScaler()
scaler.fit(data)
data = scaler.transform(data)

test = test[['PassengerId','Pclass', 'Sex', 'Age']]
resp['PassengerId'] = test['PassengerId']
test = test[['Pclass', 'Sex', 'Age']]
test['Sex'] = test['Sex'].replace('male','-1')
test['Sex'] = test['Sex'].replace('female','1')
test['Age'] = test['Age'].fillna(0)

test = scaler.transform(test)

models = []
models.append(linear_model.SGDClassifier(learning_rate="adaptive",eta0=0.0001)) 
models.append(linear_model.SGDClassifier(learning_rate="invscaling",eta0=0.01))
models.append(linear_model.SGDClassifier(learning_rate="constant",eta0=0.01))
models.append(neighbors.KNeighborsClassifier(n_neighbors=1))
models.append(neighbors.KNeighborsClassifier(n_neighbors=2))
models.append(linear_model.Lasso())



for model in models:

    model.fit(data,y)
    resp['Pred'] = model.predict(test)
    resp['Target'] = asw['Survived']

    resp['Correct'] = resp['Pred'] == resp['Target']

    print(model, resp['Correct'].sum()/total)

    asw = pd.DataFrame()

    asw['PassengerId'] = resp['PassengerId']
    asw['Survived'] = resp['Pred']

    asw.to_csv(f'resps/asw_{model}.csv',index=False)