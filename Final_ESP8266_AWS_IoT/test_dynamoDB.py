# %%
import boto3
import pandas as pd

# %%
client = boto3.client('dynamodb')

# %%
table_descr = client.describe_table(
    TableName='NodeMCU_THL'
)
table_descr

# %%
table_cont = client.scan(TableName='NodeMCU_THL')
items = table_cont['Items'] # items variable will contain a list of all the items in the table

# retrieve all the items from an AWS DynamoDB table that may contain more items 
# than the maximum number of items that can be returned in a single query.
# The limitation of a single query in AWS DynamoDB is that it can only return a maximum of 1 MB of data. 
# If the query result exceeds 1 MB, the response will contain a LastEvaluatedKey attribute, 
# which indicates that there are more items to be retrieved.
while 'LastEvaluatedKey' in response:
    response = client.scan(TableName='NodeMCU_THL', ExclusiveStartKey=response['LastEvaluatedKey'])
    items.extend(response['Items'])
items

# %% transform into a pandas dataframe
df = pd.DataFrame(items)
df = df.astype(str)
df

# %% get data from strings
for col in df.columns:
    df[col] = df[col].str.extract(r": '(.+?)'")
    df
df
