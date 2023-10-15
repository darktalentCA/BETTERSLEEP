Arduino code:
collect temperature, humidity and noise level in the room
send the information to MQTT Broker

MQTT_GCP
python code with flask framework.
subscribe MQTT Broker topic and publish the data to GCP Pub/Sbu topic
the code is deployed on GCP Cloud run

MQTT_Render
python code with flask framework.
subscribe MQTT Broker topic and publish the data to GCP Pub/Sbu topic
the code is deployed on Render

Cloud_Function_Firestore
Deployed on GCP Cloud Function
Subscribe GCP Pub/Sub topic and write the data to Firestore under firebase.
Written in Typescript

Webapp_Backend, node js backend for the application.
Notes:
To run the server: 'npm run dev'; 'dev' is defined in package.json
.env includes environment variable; use 'dotenv' to call the variable; identify if it's in production
link to tutorial: https://www.youtube.com/watch?v=jK7mcMrYzj8&list=PL-LRDpVN2fZA-1igOQ6PDcqfBjS-vaC7w
