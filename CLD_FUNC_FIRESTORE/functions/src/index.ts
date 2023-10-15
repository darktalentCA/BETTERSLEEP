import * as functions from "firebase-functions";

const admin = require("firebase-admin");
admin.initializeApp();

exports.insertFromPubsub = functions.pubsub
  .topic("humiTempSound")
  .onPublish((message, context) => {
    console.log("The function was triggered at ", context.timestamp);

    let userID = "";
    let EdgeDeviceID = "";
    let noiseLevel = "";
    let temperature = "";
    let humidity = "";
    const created = Date.now();

    try {
      userID = message.attributes.userID;
      EdgeDeviceID = message.attributes.EdgeDeviceID;
      noiseLevel = message.attributes.soundsensor;
      temperature = message.attributes.dht11temp;
      humidity = message.attributes.dht11humi;
      console.log("noiseLevel", noiseLevel);
      console.log("temperature", temperature);
      console.log("humidity", humidity);
    } catch (e) {
      functions.logger.error("PubSub message attributes error:", e);
    }

    var sensorInfo = {
      // sensorLocation: sensorLocation,
      userID: userID,
      EdgeDeviceID: EdgeDeviceID,
      noiseLevel: noiseLevel,
      temperature: temperature,
      humidity: humidity,
      created: created,
    };

    return admin.firestore().collection("humiTempSound").add(sensorInfo);
  });
