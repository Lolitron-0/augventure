import axios from "axios";

const instance = axios.create({
    baseURL: 'localhost:80/api',
})

export default instance