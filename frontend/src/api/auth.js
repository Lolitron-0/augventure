export default function(instance) {
    return {
        login(payload) {
            return instance.post('auth/login', payload)
        },
        signUp() {
            return instance.post('auth/signup', payload)
        },
        logout() {
            return instance.delete('auth/logout')
        },
    }
}