import axios from "axios";

const instance = axios.create({
	baseURL: "/api/",
});

instance.interceptors.request.use(function (config) {
    console.log("int");
    return config;
  });

export default instance;
