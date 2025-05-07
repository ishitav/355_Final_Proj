import pandas as pd
import numpy as np
from datetime import datetime
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.neighbors import NearestNeighbors
from scipy.sparse import hstack, csr_matrix


df = pd.read_csv("SocialMediaUsersDataset.csv") 


def calculate_age(dob):
    try:
        birth_date = pd.to_datetime(dob, errors='coerce')
        if pd.isnull(birth_date): return np.nan
        today = datetime.today()
        return today.year - birth_date.year - ((today.month, today.day) < (birth_date.month, birth_date.day))
    except:
        return np.nan

df['Age'] = df['DOB'].apply(calculate_age)
df.dropna(subset=['Age', 'City', 'Country', 'Interests', 'Gender', 'Name'], inplace=True)
df.reset_index(drop=True, inplace=True)


df = df.sample(n=5000, random_state=42).reset_index(drop=True)


encoder = OneHotEncoder(sparse=False, handle_unknown='ignore')
cat_features = encoder.fit_transform(df[['City', 'Country', 'Gender']])

scaler = StandardScaler()
scaled_age = scaler.fit_transform(df[['Age']])

vectorizer = CountVectorizer(tokenizer=lambda x: x.split(','), binary=True)
interest_matrix = vectorizer.fit_transform(df['Interests'].astype(str))

X_full = hstack([
    csr_matrix(scaled_age),
    csr_matrix(cat_features),
    interest_matrix
])


nn_model = NearestNeighbors(metric='cosine', algorithm='brute', n_jobs=-1)
nn_model.fit(X_full)


def recommend_top_n(user_idx, n=5):
    user_vector = X_full[user_idx]
    distances, indices = nn_model.kneighbors(user_vector, n_neighbors=n+1)
    recommendations = []
    for i, dist in zip(indices[0][1:], distances[0][1:]):
        recommendations.append({
            'Name': df.loc[i, 'Name'],
            'City': df.loc[i, 'City'],
            'Country': df.loc[i, 'Country'],
            'Gender': df.loc[i, 'Gender'],
            'Age': int(df.loc[i, 'Age']),
            'Interests': df.loc[i, 'Interests'],
            'Similarity Score': round(1 - dist, 3)
        })
    return recommendations

print("Friend Recommendation System Loaded.")
print(f"{len(df)} users loaded into memory.\n")

while True:
    print("=" * 60)
    print("Select one of these 20 random users to view recommendations:\n")

    sample_indices = df.sample(n=20, random_state=np.random.randint(0, 10000)).index.tolist()
    index_map = {i: sample_indices[i] for i in range(20)}  

    for i in range(20):
        user = df.loc[index_map[i]]
        print(f"{i:2}: {user['Name']}")
        print(f"    City: {user['City']} | Country: {user['Country']} | Age: {int(user['Age'])}")
        print(f"    Interests: {user['Interests']}\n")

    choice = input("Enter a number (0–19) to view recommendations or 'exit': ").strip()
    if choice.lower() == 'exit':
        print("Exiting system. Goodbye!")
        break
    if not choice.isdigit() or int(choice) not in range(20):
        print("Invalid choice. Please select a number between 0 and 19.\n")
        continue

    chosen_idx = index_map[int(choice)]
    chosen_user = df.loc[chosen_idx]

    print("\n" + "=" * 60)
    print(f"Top Recommendations for {chosen_user['Name']}")
    print(f"City: {chosen_user['City']} | Country: {chosen_user['Country']} | Age: {int(chosen_user['Age'])}")
    print(f"Interests: {chosen_user['Interests']}")
    print("=" * 60 + "\n")

    recs = recommend_top_n(chosen_idx)
    for r in recs:
        print(f"{r['Name']}")
        print(f"    City: {r['City']} | Country: {r['Country']} | Age: {r['Age']}")
        print(f"    Gender: {r['Gender']}")
        print(f"    Interests: {r['Interests']}")
        print(f"    Similarity Score: {r['Similarity Score']}\n")

    input("Press Enter to refresh with 20 new users...\n")