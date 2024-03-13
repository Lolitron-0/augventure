export default function (instance) {
    return {
        listSprints() {
            return instance.get("sprints");
        },
    };
}