import axios from "axios";

const instance = axios.create({
    baseURL: '/api/',
})

const token_instance = axios.create({
    baseURL: '/api/',
})
const token_interceptor = token_instance.interceptors.request.use(
    config => {
        config.headers.Authorization = localStorage.getItem("token")
        return config
    },
    error => {
        return Promise.reject(error)
    }
)


export default instance